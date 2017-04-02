#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"
#include "emfat.h"

#define AUTORUN_SIZE 50
#define README_SIZE  21
#define ICON_SIZE    1758

const char *autorun_file =
	"[autorun]\r\n"
	"label=emfat test drive\r\n"
	"ICON=icon.ico\r\n";

const char *readme_file =
	"This is readme file\r\n";

const char icon_file[ICON_SIZE] =
{
	0x00,0x00,0x01,0x00,0x01,0x00,0x18,0x18,0x00,0x00,0x01,0x00,0x08,0x00,0xc8,0x06,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x30,0x00,0x00,
	0x00,0x01,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0xa0,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0xf3,0xc9,0x66,
	0x00,0x00,0x00,0x00,0x00,0xf6,0xe9,0xea,0x00,0xea,0xb0,0x41,0x00,0xf3,0xda,0xb4,0x00,0xc4,0x6d,0x16,0x00,0xf6,0xda,0x95,0x00,0xe2,0x9e,0x24,0x00,0xfa,0xeb,0xca,
	0x00,0xf7,0xea,0xe5,0x00,0xfb,0xe6,0xa9,0x00,0xd3,0x86,0x2b,0x00,0xfc,0xf1,0xde,0x00,0xf4,0xe4,0xe3,0x00,0xf0,0xc4,0x62,0x00,0xea,0xb4,0x46,0x00,0xc6,0x73,0x1d,
	0x00,0xf9,0xef,0xe1,0x00,0xf8,0xea,0xe8,0x00,0xf9,0xe3,0xa7,0x00,0xed,0xc5,0x7c,0x00,0xe1,0x96,0x15,0x00,0xf4,0xe2,0xd7,0x00,0xfb,0xea,0xc2,0x00,0xe7,0xaa,0x39,
	0x00,0xf6,0xe2,0xc2,0x00,0xfa,0xf4,0xf1,0x00,0xeb,0xb6,0x48,0x00,0xe7,0xa6,0x2a,0x00,0xea,0xb1,0x44,0x00,0xe2,0x9d,0x23,0x00,0xf4,0xe4,0xdc,0x00,0xf3,0xe0,0xdb,
	0x00,0xe3,0xa0,0x27,0x00,0xe9,0xae,0x3e,0x00,0xfd,0xfb,0xfb,0x00,0xfa,0xf5,0xf4,0x00,0xed,0xba,0x52,0x00,0xfa,0xf1,0xee,0x00,0xf9,0xee,0xef,0x00,0xf8,0xec,0xe6,
	0x00,0xf5,0xe7,0xe0,0x00,0xf6,0xe6,0xda,0x00,0xe5,0xa4,0x30,0x00,0xf4,0xe3,0xdb,0x00,0xe4,0xa3,0x29,0x00,0xfa,0xe6,0xb1,0x00,0xf1,0xd7,0xc2,0x00,0xf7,0xd9,0x83,
	0x00,0xb9,0x61,0x15,0x00,0xff,0xfd,0xff,0x00,0xf0,0xc3,0x60,0x00,0xf0,0xc1,0x5a,0x00,0xf9,0xee,0xe7,0x00,0xf7,0xe9,0xe5,0x00,0xfa,0xed,0xd9,0x00,0xf5,0xe5,0xdf,
	0x00,0xf4,0xe2,0xdc,0x00,0xe0,0x96,0x18,0x00,0xfb,0xe8,0xb7,0x00,0xe1,0x96,0x13,0x00,0xfb,0xe4,0xad,0x00,0xf4,0xd2,0x76,0x00,0xf4,0xcd,0x71,0x00,0xe1,0x98,0x1d,
	0x00,0xef,0xbf,0x5a,0x00,0xed,0xbd,0x54,0x00,0xec,0xbb,0x4f,0x00,0xfb,0xe7,0xb5,0x00,0xf0,0xd7,0xb3,0x00,0xfb,0xe7,0xb4,0x00,0xdc,0x8f,0x13,0x00,0xfb,0xe6,0xb2,
	0x00,0xf8,0xed,0xe9,0x00,0xf7,0xeb,0xe6,0x00,0xef,0xd2,0xa9,0x00,0xdf,0xa5,0x52,0x00,0xf8,0xed,0xe8,0x00,0xf9,0xef,0xeb,0x00,0xf3,0xd4,0x92,0x00,0xfb,0xe6,0xb3,
	0x00,0xfe,0xff,0xff,0x00,0xe5,0xa4,0x2e,0x00,0xee,0xc1,0x61,0x00,0xe7,0xa7,0x2f,0x00,0xae,0x56,0x14,0x00,0xe4,0xb2,0x60,0x00,0xf9,0xe3,0xad,0x00,0xf5,0xe6,0xdf,
	0x00,0xda,0x97,0x36,0x00,0xe1,0x9a,0x1f,0x00,0xe4,0xa3,0x2c,0x00,0xec,0xb8,0x4f,0x00,0xde,0x9f,0x43,0x00,0xe1,0x9b,0x21,0x00,0xfb,0xe6,0xb4,0x00,0xf9,0xf0,0xef,
	0x00,0xee,0xbe,0x57,0x00,0xf1,0xc8,0x6f,0x00,0xf9,0xe1,0xaa,0x00,0xf9,0xee,0xeb,0x00,0xf7,0xe9,0xe3,0x00,0xfa,0xf2,0xf3,0x00,0xf6,0xd7,0x8f,0x00,0xf6,0xe8,0xe3,
	0x00,0xf5,0xdc,0xaa,0x00,0xd9,0x91,0x2c,0x00,0xe6,0xa7,0x34,0x00,0xe7,0xac,0x3c,0x00,0xde,0x92,0x1e,0x00,0xed,0xcb,0x94,0x00,0xef,0xbc,0x49,0x00,0xf4,0xe4,0xe1,
	0x00,0xf0,0xc9,0x79,0x00,0xfa,0xed,0xcd,0x00,0xe8,0xaf,0x3b,0x00,0xf3,0xcb,0x6c,0x00,0xec,0xb4,0x48,0x00,0xf2,0xc6,0x68,0x00,0xf9,0xf2,0xf4,0x00,0xf2,0xd9,0xa7,
	0x00,0xf3,0xdf,0xd8,0x00,0xf0,0xcd,0x8d,0x00,0xfa,0xf2,0xf0,0x00,0xf9,0xf3,0xf2,0x00,0xf4,0xde,0xc0,0x00,0xff,0xff,0xff,0x00,0xf7,0xe0,0xa7,0x00,0xf1,0xc9,0x63,
	0x00,0xf8,0xeb,0xe2,0x00,0xfc,0xf9,0xf8,0x00,0xfe,0xfc,0xfb,0x00,0xef,0xc1,0x58,0x00,0xfb,0xf3,0xe5,0x00,0xf4,0xe6,0xe6,0x00,0xe3,0xa1,0x2a,0x00,0xe1,0x99,0x1e,
	0x00,0xf9,0xef,0xea,0x00,0xf6,0xe8,0xe2,0x00,0xfa,0xe1,0x99,0x00,0xf7,0xe8,0xe2,0x00,0xf4,0xdf,0xca,0x00,0xfc,0xef,0xda,0x00,0xf9,0xe5,0xb0,0x00,0xf9,0xe6,0xb1,
	0x00,0xf7,0xe1,0xa8,0x00,0xfa,0xf6,0xf8,0x00,0xeb,0xba,0x4f,0x00,0xf7,0xe7,0xdc,0x00,0xe8,0xaa,0x32,0x00,0xe2,0x99,0x19,0x00,0xfa,0xdf,0x94,0x00,0xe4,0x9d,0x1b,
	0x00,0xe5,0x9e,0x1d,0x00,0xea,0xc7,0x97,0x00,0xfc,0xf6,0xf5,0x00,0xef,0xce,0x9f,0x00,0xf9,0xde,0x99,0x00,0xed,0xbc,0x4d,0x00,0xf8,0xe9,0xdb,0x00,0xf8,0xec,0xea,
	0x00,0xf5,0xe5,0xe2,0x00,0xf5,0xd1,0x78,0x00,0xf7,0xd5,0x7b,0x00,0xf3,0xd1,0x7c,0x00,0xf6,0xd3,0x7d,0x00,0xf2,0xc9,0x69,0x00,0xe9,0xaf,0x40,0x00,0xfe,0xfc,0xfd,
	0x00,0xf3,0xe2,0xdd,0x00,0xf1,0xd1,0x98,0x00,0xe8,0xb3,0x4b,0x00,0xf9,0xe3,0xab,0x00,0xf5,0xdb,0x98,0x00,0xcf,0x88,0x34,0x00,0xeb,0xb7,0x4c,0x00,0xec,0xb6,0x4e,
	0x00,0xf0,0xca,0x74,0x00,0xf6,0xd6,0x7e,0x00,0xe9,0xbb,0x60,0x00,0xc9,0x76,0x1c,0x00,0xce,0x79,0x18,0x00,0xf7,0xdd,0xa1,0x00,0xf4,0xd9,0xa6,0x00,0xf1,0xce,0x81,
	0x00,0xf1,0xcf,0x96,0x00,0xc9,0x77,0x20,0x00,0xe6,0xad,0x39,0x00,0xf8,0xec,0xe9,0x00,0xfb,0xf8,0xf6,0x00,0xfa,0xeb,0xcd,0x00,0xfb,0xe9,0xb9,0x00,0xfa,0xe9,0xbf,
	0x00,0xfc,0xea,0xbf,0x00,0xf9,0xe4,0xae,0x00,0xf4,0xe2,0xe0,0x00,0xf9,0xe6,0xaf,0x00,0xfe,0xee,0xc1,0x00,0xf9,0xf2,0xf1,0x00,0xfb,0xee,0xde,0x00,0xfa,0xf0,0xf2,
	0x00,0xf2,0xc5,0x64,0x00,0xf7,0xe9,0xee,0x00,0xf4,0xe2,0xd9,0x00,0xe6,0xa5,0x31,0x00,0xe5,0xa7,0x33,0x00,0xf6,0xe8,0xe1,0x00,0xee,0xd2,0xb0,0x00,0xf5,0xe8,0xe3,
	0x00,0xdd,0xa2,0x4e,0x00,0xfa,0xe6,0xb2,0x00,0xf8,0xdb,0x84,0x00,0xfc,0xf6,0xec,0x00,0xfa,0xe7,0xb3,0x00,0xfd,0xfa,0xf9,0x00,0xee,0xbe,0x55,0x00,0xf8,0xec,0xe8,
	0x00,0xf9,0xe7,0xc0,0x00,0xfa,0xed,0xe6,0x00,0xd0,0x7f,0x1b,0x00,0xf9,0xed,0xec,0x00,0xf3,0xcd,0x6e,0x00,0xe5,0xaa,0x38,0x00,0xe6,0xa8,0x35,0x00,0xf9,0xf0,0xed,
	0x00,0xed,0xb6,0x42,0x00,0xf8,0xdc,0x88,0x00,0xf8,0xdc,0x8e,0x00,0xf0,0xcc,0x91,0x00,0xd9,0x87,0x11,0x00,0xfb,0xef,0xdb,0x00,0xfa,0xf0,0xe4,0x00,0xfa,0xf2,0xe6,
	0x00,0xf6,0xe6,0xe5,0x00,0xfc,0xf6,0xeb,0x00,0xf4,0xe4,0xe7,0x00,0xfc,0xee,0xd3,0x00,0xf2,0xd6,0xa8,0x00,0xf9,0xee,0xec,0x00,0xf1,0xd6,0xad,0x00,0xfd,0xf9,0xf5,
	0x00,0xfc,0xf9,0xf7,0x00,0xfd,0xfb,0xf6,0x00,0xf9,0xe2,0xa9,0x00,0xfb,0xe5,0xaf,0x00,0xf5,0xcf,0x73,0x00,0xf8,0xe2,0xb8,0x00,0xf8,0xe6,0xb8,0x00,0xf1,0xcb,0x7d,
	0x00,0xec,0xb7,0x45,0x00,0xf7,0xe0,0xa3,0x00,0xff,0xfe,0xff,0x00,0xd8,0x92,0x34,0x00,0xf0,0xc3,0x5c,0x00,0xf8,0xe7,0xd0,0x00,0xff,0xff,0xff,0x00,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x0b,0x31,0x55,0x55,0x31,0x0b,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xb4,0x6d,0x99,0x98,
	0x96,0x15,0x3c,0x3c,0xe5,0x05,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x10,0x47,0x1c,0x2d,0x07,0x1e,0x5e,0x88,0x40,0x3a,0x3a,0x15,0x47,0x05,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x0b,0x54,0x73,0x6e,0xde,0x2b,0x5b,0x87,0x21,0x1e,0x5e,0x5a,0x40,0x3a,0x47,0xb5,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0xfc,0x2b,0x03,0x14,0x86,0x54,0x18,0xde,0x6b,0xcc,0x52,0x2d,0x21,0x07,0x5e,0x5a,0x47,0xdb,0x01,0x01,0x01,0x01,0x01,0xae,0x2b,0x93,0x1b,0x7a,0x02,0x25,0x22,0xa7,
	0x22,0x6c,0xde,0xdf,0xcc,0x52,0x5b,0x21,0x1e,0x47,0xba,0x01,0x01,0x01,0x01,0x2b,0x34,0x61,0x43,0xaa,0xe9,0xca,0xf9,0x0f,0x0f,0x1d,0x03,0x22,0x6c,0x18,0xcd,0xab,
	0xbb,0x21,0x0b,0x01,0x01,0x01,0xd1,0x00,0x0e,0x33,0x34,0x71,0x02,0xd0,0x2a,0xe1,0xb0,0xaf,0x1b,0x0f,0x1d,0x03,0x95,0x2f,0xeb,0xb3,0x1c,0x4c,0x01,0x01,0x2b,0x74,
	0xa6,0x76,0x0e,0xb8,0xa0,0x36,0x12,0x04,0x9e,0x42,0x25,0x5c,0xaf,0x75,0x93,0x0d,0x79,0x2f,0x14,0x9a,0x01,0x56,0x00,0x3f,0x3f,0xdd,0x00,0xb7,0x49,0x4a,0x4a,0x27,
	0xb1,0x41,0x41,0x61,0x42,0x5c,0xb9,0x70,0x16,0x20,0x9c,0x53,0x4c,0x5d,0xe3,0xa2,0x3e,0xf5,0xa4,0x77,0x49,0x4d,0x4d,0xdc,0x7d,0xfd,0x0e,0x33,0xfd,0xd7,0xf8,0xa1,
	0xcb,0x39,0xe4,0x53,0x0b,0x59,0x97,0xb2,0xa5,0x3e,0x19,0x60,0x4e,0x4e,0xe0,0xc8,0x19,0x80,0x00,0xc9,0x33,0x84,0xed,0xa1,0x2c,0xa9,0xef,0x6f,0x10,0x59,0x8b,0x30,
	0x30,0xa3,0xf6,0x7c,0x26,0x7b,0xda,0xad,0x06,0x06,0x06,0x67,0x69,0x4f,0x94,0x29,0x1f,0x39,0xc3,0xaa,0x10,0x5d,0x0a,0xd3,0xe2,0x9d,0x35,0x1a,0x24,0x37,0x63,0x13,
	0x91,0x7f,0xb6,0x9f,0x27,0xbc,0x65,0x29,0x38,0x2c,0x39,0x8d,0x6a,0x56,0xc5,0x13,0xbe,0x11,0x1a,0x08,0x37,0xf7,0xac,0x57,0x57,0x63,0xfa,0x66,0x4d,0x4a,0x09,0xce,
	0x58,0x1f,0x16,0xa1,0x4c,0x01,0x72,0x11,0x92,0x08,0x0c,0xe8,0x72,0x3b,0x2e,0x90,0x8f,0xc2,0xf3,0xc6,0x64,0xd8,0x4a,0x8c,0x29,0x1f,0x2c,0xfe,0x01,0x01,0x45,0xfe,
	0x9b,0xe6,0x85,0xd5,0x48,0x46,0x46,0x5f,0x48,0xd2,0xc4,0xd9,0x60,0x49,0x4a,0x36,0x8a,0x38,0x58,0xcf,0x01,0x01,0x01,0xfe,0xbd,0x82,0x23,0xd4,0x3d,0x50,0x44,0x44,
	0x44,0x46,0x5f,0x3d,0x35,0x64,0xa0,0xfe,0x9f,0x2a,0xfe,0x01,0x01,0x01,0x01,0x45,0xfe,0xf1,0xd6,0xfb,0x8e,0xec,0xf4,0x46,0x44,0x44,0x44,0x48,0x4e,0xee,0x81,0x09,
	0x68,0xfe,0x4b,0x01,0x01,0x01,0x01,0x01,0x45,0xfe,0x23,0xa8,0x51,0xf2,0x83,0x2e,0x44,0x44,0x44,0x46,0x0a,0x60,0x49,0x4a,0xfe,0x4b,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x45,0xfe,0x32,0x51,0x51,0xea,0x2e,0x46,0x44,0x44,0x50,0x89,0xda,0x28,0xfe,0x4b,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x45,0x0c,0x7e,0x32,0xc1,0x3b,
	0xc0,0x50,0x46,0x48,0xbf,0xc7,0xfe,0x04,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x45,0xfe,0xec,0xf0,0x9b,0x17,0x08,0xe7,0x17,0x78,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x45,0x4f,0x62,0x62,0x4f,0x45,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xff,0x81,0xff,
	0x00,0xfe,0x00,0x7f,0x00,0xf8,0x00,0x1f,0x00,0xf0,0x00,0x0f,0x00,0xe0,0x00,0x07,0x00,0xc0,0x00,0x03,0x00,0xc0,0x00,0x03,0x00,0x80,0x00,0x01,0x00,0x80,0x00,0x01,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x01,0x00,0x80,0x00,0x01,
	0x00,0xc0,0x00,0x03,0x00,0xc0,0x00,0x03,0x00,0xe0,0x00,0x07,0x00,0xf0,0x00,0x0f,0x00,0xf8,0x00,0x1f,0x00,0xfe,0x00,0x7f,0x00,0xff,0x81,0xff,0x00
};

USB_OTG_CORE_HANDLE USB_OTG_dev;

// ��������� ����������� �������� ������� FAT32
emfat_t emfat;

// callback ������� ������ ������
void autorun_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata);
void icon_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata);
void readme_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata);

#define CMA_TIME EMFAT_ENCODE_CMA_TIME(2,4,2017, 13,0,0)
#define CMA { CMA_TIME, CMA_TIME, CMA_TIME }

// ��������� ��
static emfat_entry_t entries[] =
{
	// name          dir    lvl offset  size             max_size        user  time  read               write
	{ "",            true,  0,  0,      0,               0,              0,    CMA,  NULL,              NULL }, // root
	{ "autorun.inf", false, 1,  0,      AUTORUN_SIZE,    AUTORUN_SIZE,   0,    CMA,  autorun_read_proc, NULL }, // autorun.inf
	{ "icon.ico",    false, 1,  0,      ICON_SIZE,       ICON_SIZE,      0,    CMA,  icon_read_proc,    NULL }, // icon.ico
	{ "drivers",     true,  1,  0,      0,               0,              0,    CMA,  NULL,              NULL }, // drivers/
	{ "readme.txt",  false, 2,  0,      README_SIZE,     1024*1024,      0,    CMA,  readme_read_proc,  NULL }, // drivers/readme.txt
	{ NULL }
};

/*
static emfat_entry_t entries[] =
{
	// name          dir    lvl offset  size             max_size        user  read               write
	{ "",            true,  0,  0,      0,               0,              0,    NULL,              NULL }, // root
	{ "autorun.inf", false, 1,  0,      AUTORUN_SIZE,    1*1024*1024*1024,   0,    autorun_read_proc, NULL }, // autorun.inf
	{ "icon.ico",    false, 1,  0,      ICON_SIZE,       1*1024*1024*1024,      0,    icon_read_proc,    NULL }, // icon.ico
	{ "drivers",     true,  1,  0,      0,               0,              0,    NULL,              NULL }, // drivers/
	{ "readme.txt",  false, 2,  0,      README_SIZE,     1*1024*1024*1024,    0,    readme_read_proc,  NULL }, // drivers/readme.txt
	{ "abc.txt",  false, 2,  0,      README_SIZE,     1*1024*1024*1024-32768+8192,    0,    readme_read_proc,  NULL }, // drivers/readme.txt
	{ NULL }
};
*/
void autorun_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata)
{
	int len = 0;
	if (offset > AUTORUN_SIZE) return;
	if (offset + size > AUTORUN_SIZE)
		len = AUTORUN_SIZE - offset; else
		len = size;
	memcpy(dest, &autorun_file[offset], len);
}

void icon_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata)
{
	int len = 0;
	if (offset > ICON_SIZE) return;
	if (offset + size > ICON_SIZE)
		len = ICON_SIZE - offset; else
		len = size;
	memcpy(dest, &icon_file[offset], len);
}

void readme_read_proc(uint8_t *dest, int size, uint32_t offset, size_t userdata)
{
	int len = 0;
	if (offset > README_SIZE) return;
	if (offset + size > README_SIZE)
		len = README_SIZE - offset; else
		len = size;
	memcpy(dest, &readme_file[offset], len);
}

int main(void)
{
	emfat_init(&emfat, "emfat", entries);

#ifdef USE_USB_OTG_HS
  USBD_Init(&USB_OTG_dev, USB_OTG_HS_CORE_ID, &USR_desc, &USBD_MSC_cb, &USR_cb);
#else
  USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_MSC_cb, &USR_cb);
#endif

  while (true)
	{
	}
}
