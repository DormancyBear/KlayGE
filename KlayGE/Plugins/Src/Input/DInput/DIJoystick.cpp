// DIJoystick.cpp
// KlayGE DInput游戏杆管理类 实现文件
// Ver 2.0.0
// 版权所有(C) 龚敏敏, 2003
// Homepage: http://www.enginedev.com
//
// 2.0.0
// 初次建立 (2003.8.30)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/ThrowErr.hpp>

#include <KlayGE/DInput/DInput.hpp>

namespace KlayGE
{
	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	DInputJoystick::DInputJoystick(REFGUID guid, InputEngine& inputEng)
	{
		DInputEngine& dinputEng(reinterpret_cast<DInputEngine&>(inputEng));

		IDirectInputDevice8W* device;
		dinputEng.DInput()->CreateDevice(guid, &device, NULL);
		device_ = COMPtr<IDirectInputDevice8W>(device);

		device_->SetDataFormat(&c_dfDIJoystick);
		device_->SetCooperativeLevel(::GetForegroundWindow(), DISCL_EXCLUSIVE | DISCL_BACKGROUND);

		// Set the X-axis range (-1000 to +1000)
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		TIF(device_->SetProperty(DIPROP_RANGE, &diprg.diph));

		// And again for Y-axis range
		diprg.diph.dwObj = DIJOFS_Y;

		TIF(device_->SetProperty(DIPROP_RANGE, &diprg.diph));

		// Set X axis dead zone to 10%
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = DIJOFS_X;
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = 1000;

		TIF(device_->SetProperty(DIPROP_DEADZONE, &dipdw.diph));

		dipdw.diph.dwObj = DIJOFS_Y;

		// Set Y axis dead zone to 10%
		TIF(device_->SetProperty(DIPROP_DEADZONE, &dipdw.diph));

		this->Acquire();
	}

	// 析构函数
	/////////////////////////////////////////////////////////////////////////////////
	DInputJoystick::~DInputJoystick()
	{
		this->Unacquire();
	}

	// 设备名称
	//////////////////////////////////////////////////////////////////////////////////
	const WString& DInputJoystick::Name() const
	{
		static WString name(L"DirectInput Joystick");
		return name;
	}

	// 获取设备
	/////////////////////////////////////////////////////////////////////////////////
	void DInputJoystick::Acquire()
	{
		TIF(device_->Acquire());
	}

	// 释放设备
	//////////////////////////////////////////////////////////////////////////////////
	void DInputJoystick::Unacquire()
	{
		TIF(device_->Unacquire());
	}

	// 更新游戏杆状态
	/////////////////////////////////////////////////////////////////////////////////
	void DInputJoystick::UpdateKeys()
	{
		device_->Poll();

		DIJOYSTATE diJoyState;
		bool done;
		do
		{
			HRESULT hr(device_->GetDeviceState(sizeof(diJoyState), &diJoyState));
			if ((DIERR_INPUTLOST == hr) || (DIERR_NOTACQUIRED == hr))
			{
				this->Acquire();
				done = false;
			}
			else
			{
				done = true;
			}
		} while (!done);

		xPos_ = diJoyState.lX;
		yPos_ = diJoyState.lY;
		zPos_ = diJoyState.lZ;
		xRot_ = diJoyState.lRx;
		yRot_ = diJoyState.lRy;
		zRot_ = diJoyState.lRz;

		for (size_t i = 0; i < slider_.size(); ++ i)
		{
			slider_[i] = diJoyState.rglSlider[i];
		}

		for (size_t i = 0; i < buttons_.size(); ++ i)
		{
			buttons_[i] = (diJoyState.rgbButtons[i] != 0);
		}
	}
}
