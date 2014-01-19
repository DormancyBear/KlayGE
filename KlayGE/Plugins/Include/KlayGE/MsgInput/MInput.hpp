/**
 * @file MInput.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef _MINPUT_HPP
#define _MINPUT_HPP

#pragma once

#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP
#include <windows.h>
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <hidsdi.h>
#else
#ifndef _NTDEF_
typedef LONG NTSTATUS;
#endif

typedef USHORT USAGE, *PUSAGE;

#define HID_USAGE_PAGE_UNDEFINED                        ((USAGE) 0x00)
#define HID_USAGE_PAGE_GENERIC                          ((USAGE) 0x01)
#define HID_USAGE_PAGE_SIMULATION                       ((USAGE) 0x02)
#define HID_USAGE_PAGE_VR                               ((USAGE) 0x03)
#define HID_USAGE_PAGE_SPORT                            ((USAGE) 0x04)
#define HID_USAGE_PAGE_GAME                             ((USAGE) 0x05)
#define HID_USAGE_PAGE_KEYBOARD                         ((USAGE) 0x07)
#define HID_USAGE_PAGE_LED                              ((USAGE) 0x08)
#define HID_USAGE_PAGE_BUTTON                           ((USAGE) 0x09)
#define HID_USAGE_PAGE_ORDINAL                          ((USAGE) 0x0A)
#define HID_USAGE_PAGE_TELEPHONY                        ((USAGE) 0x0B)
#define HID_USAGE_PAGE_CONSUMER                         ((USAGE) 0x0C)
#define HID_USAGE_PAGE_DIGITIZER                        ((USAGE) 0x0D)
#define HID_USAGE_PAGE_UNICODE                          ((USAGE) 0x10)
#define HID_USAGE_PAGE_ALPHANUMERIC                     ((USAGE) 0x14)
#define HID_USAGE_PAGE_MICROSOFT_BLUETOOTH_HANDSFREE    ((USAGE) 0xFFF3)

#define HID_USAGE_GENERIC_POINTER      ((USAGE) 0x01)
#define HID_USAGE_GENERIC_MOUSE        ((USAGE) 0x02)
#define HID_USAGE_GENERIC_JOYSTICK     ((USAGE) 0x04)
#define HID_USAGE_GENERIC_GAMEPAD      ((USAGE) 0x05)
#define HID_USAGE_GENERIC_KEYBOARD     ((USAGE) 0x06)
#define HID_USAGE_GENERIC_KEYPAD       ((USAGE) 0x07)
#define HID_USAGE_GENERIC_SYSTEM_CTL   ((USAGE) 0x80)

#define HID_USAGE_GENERIC_X                        ((USAGE) 0x30)
#define HID_USAGE_GENERIC_Y                        ((USAGE) 0x31)
#define HID_USAGE_GENERIC_Z                        ((USAGE) 0x32)
#define HID_USAGE_GENERIC_RX                       ((USAGE) 0x33)
#define HID_USAGE_GENERIC_RY                       ((USAGE) 0x34)
#define HID_USAGE_GENERIC_RZ                       ((USAGE) 0x35)
#define HID_USAGE_GENERIC_SLIDER                   ((USAGE) 0x36)
#define HID_USAGE_GENERIC_DIAL                     ((USAGE) 0x37)

typedef enum _HIDP_REPORT_TYPE
{
	HidP_Input,
	HidP_Output,
	HidP_Feature
} HIDP_REPORT_TYPE;

typedef struct _HIDP_PREPARSED_DATA * PHIDP_PREPARSED_DATA;

typedef struct _HIDP_CAPS
{
	USAGE    Usage;
	USAGE    UsagePage;
	USHORT   InputReportByteLength;
	USHORT   OutputReportByteLength;
	USHORT   FeatureReportByteLength;
	USHORT   Reserved[17];

	USHORT   NumberLinkCollectionNodes;

	USHORT   NumberInputButtonCaps;
	USHORT   NumberInputValueCaps;
	USHORT   NumberInputDataIndices;

	USHORT   NumberOutputButtonCaps;
	USHORT   NumberOutputValueCaps;
	USHORT   NumberOutputDataIndices;

	USHORT   NumberFeatureButtonCaps;
	USHORT   NumberFeatureValueCaps;
	USHORT   NumberFeatureDataIndices;
} HIDP_CAPS, *PHIDP_CAPS;

typedef struct _HIDP_BUTTON_CAPS
{
	USAGE    UsagePage;
	UCHAR    ReportID;
	BOOLEAN  IsAlias;

	USHORT   BitField;
	USHORT   LinkCollection;   // A unique internal index pointer

	USAGE    LinkUsage;
	USAGE    LinkUsagePage;

	BOOLEAN  IsRange;
	BOOLEAN  IsStringRange;
	BOOLEAN  IsDesignatorRange;
	BOOLEAN  IsAbsolute;

	ULONG    Reserved[10];
	union {
		struct {
			USAGE    UsageMin,         UsageMax;
			USHORT   StringMin,        StringMax;
			USHORT   DesignatorMin,    DesignatorMax;
			USHORT   DataIndexMin,     DataIndexMax;
		} Range;
		struct  {
			USAGE    Usage,            Reserved1;
			USHORT   StringIndex,      Reserved2;
			USHORT   DesignatorIndex,  Reserved3;
			USHORT   DataIndex,        Reserved4;
		} NotRange;
	};

} HIDP_BUTTON_CAPS, *PHIDP_BUTTON_CAPS;

typedef struct _HIDP_VALUE_CAPS
{
	USAGE    UsagePage;
	UCHAR    ReportID;
	BOOLEAN  IsAlias;

	USHORT   BitField;
	USHORT   LinkCollection;   // A unique internal index pointer

	USAGE    LinkUsage;
	USAGE    LinkUsagePage;

	BOOLEAN  IsRange;
	BOOLEAN  IsStringRange;
	BOOLEAN  IsDesignatorRange;
	BOOLEAN  IsAbsolute;

	BOOLEAN  HasNull;        // Does this channel have a null report   union
	UCHAR    Reserved;
	USHORT   BitSize;        // How many bits are devoted to this value?

	USHORT   ReportCount;    // See Note below.  Usually set to 1.
	USHORT   Reserved2[5];

	ULONG    UnitsExp;
	ULONG    Units;

	LONG     LogicalMin,       LogicalMax;
	LONG     PhysicalMin,      PhysicalMax;

	union {
		struct {
			USAGE    UsageMin,         UsageMax;
			USHORT   StringMin,        StringMax;
			USHORT   DesignatorMin,    DesignatorMax;
			USHORT   DataIndexMin,     DataIndexMax;
		} Range;

		struct {
			USAGE    Usage,            Reserved1;
			USHORT   StringIndex,      Reserved2;
			USHORT   DesignatorIndex,  Reserved3;
			USHORT   DataIndex,        Reserved4;
		} NotRange;
	};
} HIDP_VALUE_CAPS, *PHIDP_VALUE_CAPS;

#ifndef FACILITY_HID_ERROR_CODE
#define FACILITY_HID_ERROR_CODE 0x11
#endif

#define HIDP_ERROR_CODES(SEV, CODE) \
		((NTSTATUS) (((SEV) << 28) | (FACILITY_HID_ERROR_CODE << 16) | (CODE)))

#define HIDP_STATUS_SUCCESS                  (HIDP_ERROR_CODES(0x0,0))
#endif

#if (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
#include <LocationApi.h>
#include <SensorsApi.h>
#include <Sensors.h>
#endif

#endif

#include <KlayGE/Input.hpp>
#include <KFL/Timer.hpp>
#include <boost/noncopyable.hpp>

namespace KlayGE
{
	class MsgInputEngine : boost::noncopyable, public InputEngine
	{
	public:
		MsgInputEngine();
		~MsgInputEngine();

		std::wstring const & Name() const;
		void EnumDevices();

#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP
		NTSTATUS HidP_GetCaps(PHIDP_PREPARSED_DATA PreparsedData, PHIDP_CAPS Capabilities) const;
		NTSTATUS HidP_GetButtonCaps(HIDP_REPORT_TYPE ReportType, PHIDP_BUTTON_CAPS ButtonCaps,
			PUSHORT ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData) const;
		NTSTATUS HidP_GetValueCaps(HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps,
			PUSHORT ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData) const;
		NTSTATUS HidP_GetUsages(HIDP_REPORT_TYPE ReportType, USAGE UsagePage,
			USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData,
			PCHAR Report, ULONG ReportLength) const;
		NTSTATUS HidP_GetUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage,
			USHORT LinkCollection, USAGE Usage, PULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData,
			PCHAR Report, ULONG ReportLength) const;

#if (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
		BOOL RegisterTouchWindow(HWND hWnd, ULONG ulFlags) const;
		BOOL GetTouchInputInfo(HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize) const;
		BOOL CloseTouchInputHandle(HTOUCHINPUT hTouchInput) const;
#endif
#endif

	private:
		boost::signals2::connection on_raw_input_;
		boost::signals2::connection on_touch_;
		boost::signals2::connection on_pointer_down_;
		boost::signals2::connection on_pointer_up_;
		boost::signals2::connection on_pointer_update_;
		boost::signals2::connection on_pointer_wheel_;

#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP
		HMODULE mod_hid_;
		typedef NTSTATUS (WINAPI *HidP_GetCapsFunc)(PHIDP_PREPARSED_DATA PreparsedData, PHIDP_CAPS Capabilities);
		typedef NTSTATUS (WINAPI *HidP_GetButtonCapsFunc)(HIDP_REPORT_TYPE ReportType, PHIDP_BUTTON_CAPS ButtonCaps,
			PUSHORT ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData);
		typedef NTSTATUS (WINAPI *HidP_GetValueCapsFunc)(HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps,
			PUSHORT ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData);
		typedef NTSTATUS (WINAPI *HidP_GetUsagesFunc)(HIDP_REPORT_TYPE ReportType, USAGE UsagePage,
			USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData,
			PCHAR Report, ULONG ReportLength);
		typedef NTSTATUS (WINAPI *HidP_GetUsageValueFunc)(HIDP_REPORT_TYPE ReportType, USAGE UsagePage,
			USHORT LinkCollection, USAGE Usage, PULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData,
			PCHAR Report, ULONG ReportLength);
		HidP_GetCapsFunc DynamicHidP_GetCaps_;
		HidP_GetButtonCapsFunc DynamicHidP_GetButtonCaps_;
		HidP_GetValueCapsFunc DynamicHidP_GetValueCaps_;
		HidP_GetUsagesFunc DynamicHidP_GetUsages_;
		HidP_GetUsageValueFunc DynamicHidP_GetUsageValue_;

#if (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
		typedef BOOL (WINAPI *RegisterTouchWindowFunc)(HWND hWnd, ULONG ulFlags);
		typedef BOOL (WINAPI *GetTouchInputInfoFunc)(HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize);
		typedef BOOL (WINAPI *CloseTouchInputHandleFunc)(HTOUCHINPUT hTouchInput);
		RegisterTouchWindowFunc DynamicRegisterTouchWindow_;
		GetTouchInputInfoFunc DynamicGetTouchInputInfo_;
		CloseTouchInputHandleFunc DynamicCloseTouchInputHandle_;
#endif
#endif

	private:
#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP
		void OnRawInput(Window const & wnd, HRAWINPUT ri);
#if (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
		void OnTouch(Window const & wnd, HTOUCHINPUT hti, uint32_t num_inputs);
#endif
#endif
		void OnPointerDown(int2 const & pt, uint32_t id);
		void OnPointerUp(int2 const & pt, uint32_t id);
		void OnPointerUpdate(int2 const & pt, uint32_t id, bool down);
		void OnPointerWheel(int2 const & pt, uint32_t id, int32_t wheel_delta);
	};

#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP
	class MsgInputKeyboard : public InputKeyboard
	{
	public:
		MsgInputKeyboard(HWND hwnd, HANDLE device);

		virtual std::wstring const & Name() const KLAYGE_OVERRIDE;
		void OnRawInput(RAWINPUT const & ri);

	private:
		virtual void UpdateInputs() KLAYGE_OVERRIDE;

	private:
		HWND hwnd_;
		HANDLE device_;
		array<bool, 256> keys_state_;
	};

	class MsgInputMouse : public InputMouse
	{
	public:
		MsgInputMouse(HWND hwnd, HANDLE device);

		virtual std::wstring const & Name() const KLAYGE_OVERRIDE;
		void OnRawInput(RAWINPUT const & ri);

	private:
		virtual void UpdateInputs() KLAYGE_OVERRIDE;

	private:
		HWND hwnd_;
		HANDLE device_;
		int3 offset_state_;
		array<bool, 8> buttons_state_;
	};

	class MsgInputJoystick : public InputJoystick
	{
	public:
		explicit MsgInputJoystick(HANDLE device);

		virtual std::wstring const & Name() const KLAYGE_OVERRIDE;
		void OnRawInput(RAWINPUT const & ri);

	private:
		virtual void UpdateInputs() KLAYGE_OVERRIDE;

	private:
		HANDLE device_;
		int3 pos_state_;
		int3 rot_state_;
		int2 slider_state_;
		array<bool, 32> buttons_state_;
	};
#endif

	class MsgInputTouch : public InputTouch
	{
	public:
		MsgInputTouch();

		virtual std::wstring const & Name() const KLAYGE_OVERRIDE;
#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP && (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
		void OnTouch(Window const & wnd, HTOUCHINPUT hti, uint32_t num_inputs);
#endif
		void OnPointerDown(int2 const & pt, uint32_t id);
		void OnPointerUp(int2 const & pt, uint32_t id);
		void OnPointerUpdate(int2 const & pt, uint32_t id, bool down);
		void OnPointerWheel(int2 const & pt, uint32_t id, int32_t wheel_delta);

	private:
		virtual void UpdateInputs() KLAYGE_OVERRIDE;

		Timer timer_;
		array<int2, 16> touch_coord_state_;
		array<bool, 16> touch_down_state_;
		int32_t wheel_delta_state_;
	};
	
#if defined KLAYGE_PLATFORM_WINDOWS_DESKTOP && (_WIN32_WINNT >= 0x0601 /*_WIN32_WINNT_WIN7*/)
	class MsgInputSensor : public InputSensor
	{
	public:
		MsgInputSensor();

		virtual std::wstring const & Name() const KLAYGE_OVERRIDE;

	private:
		virtual void UpdateInputs() KLAYGE_OVERRIDE;

	private:
		shared_ptr<ILocation> location_sensor_;
		shared_ptr<ISensorCollection> motion_sensor_collection_;
		shared_ptr<ISensorCollection> orientation_sensor_collection_;
	};
#endif
}

#endif		// _MINPUT_HPP
