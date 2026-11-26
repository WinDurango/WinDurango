//Credits to RSantila for doing this!
#pragma once

#include <windows.h>

struct AVCodecContext;
struct AVPacket;
struct AVFrame;

// One hardware XMA decoder context, emulated with libavcodec's xma2 decoder.
//
// The bitstream the title hands over is a run of 2 KB packets, each opening with a 32 bit
// big-endian header:
//
//     frameCount  : 6    frames that *start* in this packet
//     frameOffset : 15   bit position of the first of them, counted from the end of the header
//     metadata    : 3
//     skip        : 8    packets to step over to reach the next packet of this stream
//
// Whole packets are what libavcodec wants, and whole packets are what the title's input buffers
// hold, so nothing has to be re-cut on the way through. The header is still read, for two reasons:
// `skip` decides which packet comes next, and the position of the first frame is what the shared
// context's offsetRead is reported as, which is how the title watches the decoder's progress.
//
// Frames themselves are 512 samples per channel and chain by a 15 bit length in bits, and one may
// run past the end of its packet and continue after the next packet's header. That only matters to
// the decoder's own state machine, which is why it is fed packets in order and never reset in the
// middle of a buffer. Verified against Media\Audio\FmodAnthem\DURANGO\HZ2_MX_Radio_01_Tracks.bank:
// a packet driven walk runs 3075 frames across 512 packets with no bad length, coming to 32.8
// seconds, which matches the 256 kbit/s the file is encoded at.
class XmaVoice
{
public:
    // Packet geometry, public because the caller works in the same units: the shared context's
    // offsetRead is a bit position in a buffer measured in these packets.
    static UINT32 constexpr c_PacketBytes = 2048;
    static UINT32 constexpr c_PacketBits = c_PacketBytes * 8;
    static UINT32 constexpr c_HeaderBits = 32;
    static UINT32 constexpr c_FrameSamples = 512;

    ~XmaVoice();

    // Points the voice at an input buffer. A call that names the buffer it is already reading is
    // ignored, so this is safe on every pass of the flowgraph.
    // `skipAtStart` is the context's numSubframesToSkip turned into samples: the encoder delay the
    // title wants thrown away, and it only applies to the first buffer of a stream.
    void SetInput(unsigned char const *buffer, UINT32 packetCount, UINT32 startBit, UINT32 channels,
                  UINT32 skipAtStart);

    // Fills `out` with up to `count` samples of one channel. A short return means the input ran dry
    // and the title has not refilled it yet; the caller pads with silence.
    UINT32 Take(UINT32 channel, float *out, UINT32 count);

    // Bit position within the current buffer, for the shared context's offsetRead.
    UINT32 BitOffset() const;
    bool Exhausted() const { return _exhausted; }

    UINT32 Queued(UINT32 channel) const { return channel < c_MaxChannels ? _count[channel] : 0; }
    bool Primed() const { return _primed; }
    UINT32 PacketsFed() const { return _packetsFed; }
    UINT32 FramesDecoded() const { return _framesDecoded; }
    UINT32 DecodeErrors() const { return _decodeErrors; }
    UINT32 LastError() const { return _lastError; }

    // Lets go of the input buffer without touching anything else. This is what a buffer handover
    // does: the title may refill that half the moment we stop reading it, but the samples already
    // decoded out of it have not been handed on yet, and the decoder's own inter-frame state has to
    // carry into the next half or the stream restarts every 64 milliseconds.
    void ReleaseInput();

    // Drops queued samples as well. For a voice being torn down, not for a handover.
    void Reset();

private:
    bool OpenCodec(UINT32 channels);
    void CloseCodec();
    bool FeedNextPacket();
    void DrainDecoder();
    bool DrainOneFrame();
    void Push(float const *samples, UINT32 count, UINT32 channel);

    static UINT32 constexpr c_MaxChannels = 2;

    // A packet decodes to about six frames of 512 samples, and a whole input buffer is two packets,
    // so a queue has to hold the best part of 6000 samples without dropping any. The flowgraph also
    // asks for one channel at a time, which leaves one queue a block ahead of the other.
    static UINT32 constexpr c_QueueSamples = 8192;

    unsigned char const *_buffer = nullptr;
    UINT32 _packets = 0;
    UINT32 _packet = 0;
    bool _exhausted = true;

    AVCodecContext *_codec = nullptr;
    AVPacket *_avPacket = nullptr;
    AVFrame *_avFrame = nullptr;
    UINT32 _channels = 0;

    float _queue[c_MaxChannels][c_QueueSamples]{};
    UINT32 _head[c_MaxChannels]{};
    UINT32 _count[c_MaxChannels]{};

    // Nothing leaves the voice until it holds enough to keep going. Starting to play the moment the
    // first samples arrive is what put a gap in the audio a fifth of a second later: the decoder
    // needs several packets before it emits anything, so the queue was empty again almost at once.
    // Forty milliseconds of lead covers that and costs nothing that is heard.
    static UINT32 constexpr c_PrimeSamples = 2048;
    bool _primed = false;

    UINT32 _skipRemaining[c_MaxChannels]{};
    UINT32 _packetsFed = 0;
    UINT32 _framesDecoded = 0;
    UINT32 _decodeErrors = 0;
    UINT32 _lastError = 0;
};
