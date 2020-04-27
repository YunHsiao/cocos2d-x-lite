#pragma once

#import <Metal/MTLRenderCommandEncoder.h>

NS_CC_BEGIN

class CCMTLFrameBuffer;
struct CCMTLGPUPipelineState;
class CCMTLInputAssembler;
class CCMTLBindingLayout;
class CCMTLPipelineState;

struct CCMTLDepthBias
{
    float depthBias = 0.0f;
    float slopeScale = 0.0f;
    float clamp = 0.0f;
};

struct CCMTLDepthBounds
{
    float minBounds = 0.0f;
    float maxBounds = 0.0f;
};

class CCMTLCmdBeginRenderPass : public GFXCmd
{
public:
    GFXRect renderArea;
    GFXClearFlags clearFlags = GFXClearFlags::NONE;
    CCMTLFrameBuffer* frameBuffer = nullptr;
    uint numOfClearColor = 0;
    GFXColor clearColors[GFX_MAX_ATTACHMENTS];
    float clearDepth = 1.f;
    int clearStencil = 0;
    
    CCMTLCmdBeginRenderPass() : GFXCmd(GFXCmdType::BEGIN_RENDER_PASS) {}
    
    virtual void clear() override
    {
        numOfClearColor = 0;
    }
};

class CCMTLCmdBindStates : public GFXCmd
{
public:
    GFXBindingLayout* bindingLayout = nullptr;
    CCMTLPipelineState* pipelineState = nullptr;
    CCMTLInputAssembler* inputAssembler = nullptr;
    MTLViewport viewport = {};
    MTLScissorRect scissorRect = {};
    CCMTLDepthBias depthBias;
    CCMTLDepthBounds depthBounds;
    GFXColor blendConstants;
    bool viewportDirty = false;
    bool scissorDirty = false;
    
    CCMTLCmdBindStates() : GFXCmd(GFXCmdType::BIND_STATES) {}
    
    virtual void clear() override {}
};

class CCMTLCmdDraw : public GFXCmd
{
public:
    GFXDrawInfo drawInfo;
    
    CCMTLCmdDraw() : GFXCmd(GFXCmdType::DRAW) {}
    virtual void clear() override {}
};

class CCMTLCmdCopyBufferToTexture : public GFXCmd
{
public:
    CCMTLCmdCopyBufferToTexture(): GFXCmd(GFXCmdType::COPY_BUFFER_TO_TEXTURE) {}
    virtual void clear() override {}
};

class CCMTLCmdUpdateBuffer : public GFXCmd {
public:
    uint8_t* buffer = nullptr;
    uint size = 0;
    uint offset = 0;
    
    CCMTLCmdUpdateBuffer() : GFXCmd(GFXCmdType::UPDATE_BUFFER) {}
    
    void clear() {
        buffer = nullptr;
    }
};

class CCMTLCommandPackage : public Object
{
public:
    CachedArray<GFXCmdType> commandTypes;
    CachedArray<CCMTLCmdBeginRenderPass*> beginRenderPassCmds;
    CachedArray<CCMTLCmdBindStates*> bindStatesCmds;
    CachedArray<CCMTLCmdDraw*> drawCmds;
    CachedArray<CCMTLCmdUpdateBuffer*> updateBufferCmds;
    CachedArray<CCMTLCmdCopyBufferToTexture*> copyBufferToTextureCmds;
};

NS_CC_END