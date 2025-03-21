#pragma once

#include <Windows.h>
#include <wdf.h>
#include <wrl.h>
#include <d3d12.h>
#include <stdint.h>

class CSwapChainProcessor;

using namespace Microsoft::WRL;

class CFrameBufferResource
{
  private:
    bool                   m_valid;
    uint8_t              * m_base;
    size_t                 m_size;
    ComPtr<ID3D12Resource> m_res;

  public:
    bool Init(CSwapChainProcessor * swapChain, uint8_t * base, size_t size);
    void Reset();

    bool      IsValid() { return m_valid; }
    uint8_t * GetBase() { return m_base;  }
    size_t    GetSize() { return m_size;  }

    ComPtr<ID3D12Resource> Get() { return m_res; }
};
