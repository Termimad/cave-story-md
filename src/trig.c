#include "common.h"

const s16 sin[0x100] = {
	0x0000, 0x0006, 0x000d, 0x0013, 0x0019, 0x001f, 0x0026, 0x002c, 
	0x0032, 0x0038, 0x003f, 0x0045, 0x004b, 0x0051, 0x0058, 0x005e, 
	0x0064, 0x006a, 0x0070, 0x0076, 0x007c, 0x0082, 0x0089, 0x008f, 
	0x0095, 0x009b, 0x00a1, 0x00a7, 0x00ac, 0x00b2, 0x00b8, 0x00be, 
	0x00c4, 0x00ca, 0x00cf, 0x00d5, 0x00db, 0x00e1, 0x00e6, 0x00ec, 
	0x00f1, 0x00f7, 0x00fc, 0x0102, 0x0107, 0x010d, 0x0112, 0x0117, 
	0x011c, 0x0122, 0x0127, 0x012c, 0x0131, 0x0136, 0x013b, 0x0140, 
	0x0145, 0x014a, 0x014e, 0x0153, 0x0158, 0x015c, 0x0161, 0x0166, 
	0x0200, 0x0166, 0x0161, 0x015c, 0x0158, 0x0153, 0x014e, 0x014a, 
	0x0145, 0x0140, 0x013b, 0x0136, 0x0131, 0x012c, 0x0127, 0x0122, 
	0x011c, 0x0117, 0x0112, 0x010d, 0x0107, 0x0102, 0x00fc, 0x00f7, 
	0x00f1, 0x00ec, 0x00e6, 0x00e1, 0x00db, 0x00d5, 0x00cf, 0x00ca, 
	0x00c4, 0x00be, 0x00b8, 0x00b2, 0x00ac, 0x00a7, 0x00a1, 0x009b, 
	0x0095, 0x008f, 0x0089, 0x0082, 0x007c, 0x0076, 0x0070, 0x006a, 
	0x0064, 0x005e, 0x0058, 0x0051, 0x004b, 0x0045, 0x003f, 0x0038, 
	0x0032, 0x002c, 0x0026, 0x001f, 0x0019, 0x0013, 0x000d, 0x0006, 
	0x0000, 0xfffa, 0xfff3, 0xffed, 0xffe7, 0xffe1, 0xffda, 0xffd4, 
	0xffce, 0xffc8, 0xffc1, 0xffbb, 0xffb5, 0xffaf, 0xffa8, 0xffa2, 
	0xff9c, 0xff96, 0xff90, 0xff8a, 0xff84, 0xff7e, 0xff77, 0xff71, 
	0xff6b, 0xff65, 0xff5f, 0xff59, 0xff54, 0xff4e, 0xff48, 0xff42, 
	0xff3c, 0xff36, 0xff31, 0xff2b, 0xff25, 0xff1f, 0xff1a, 0xff14, 
	0xff0f, 0xff09, 0xff04, 0xfefe, 0xfef9, 0xfef3, 0xfeee, 0xfee9, 
	0xfee4, 0xfede, 0xfed9, 0xfed4, 0xfecf, 0xfeca, 0xfec5, 0xfec0, 
	0xfebb, 0xfeb6, 0xfeb2, 0xfead, 0xfea8, 0xfea4, 0xfe9f, 0xfe9a, 
	0xfe00, 0xfe9a, 0xfe9f, 0xfea4, 0xfea8, 0xfead, 0xfeb2, 0xfeb6, 
	0xfebb, 0xfec0, 0xfec5, 0xfeca, 0xfecf, 0xfed4, 0xfed9, 0xfede, 
	0xfee4, 0xfee9, 0xfeee, 0xfef3, 0xfef9, 0xfefe, 0xff04, 0xff09, 
	0xff0f, 0xff14, 0xff1a, 0xff1f, 0xff25, 0xff2b, 0xff31, 0xff36, 
	0xff3c, 0xff42, 0xff48, 0xff4e, 0xff54, 0xff59, 0xff5f, 0xff65, 
	0xff6b, 0xff71, 0xff77, 0xff7e, 0xff84, 0xff8a, 0xff90, 0xff96, 
	0xff9c, 0xffa2, 0xffa8, 0xffaf, 0xffb5, 0xffbb, 0xffc1, 0xffc8, 
	0xffce, 0xffd4, 0xffda, 0xffe1, 0xffe7, 0xffed, 0xfff3, 0xfffa, 
};

const s16 cos[0x100] = {
	0x0200, 0x0166, 0x0161, 0x015c, 0x0158, 0x0153, 0x014e, 0x014a, 
	0x0145, 0x0140, 0x013b, 0x0136, 0x0131, 0x012c, 0x0127, 0x0122, 
	0x011c, 0x0117, 0x0112, 0x010d, 0x0107, 0x0102, 0x00fc, 0x00f7, 
	0x00f1, 0x00ec, 0x00e6, 0x00e1, 0x00db, 0x00d5, 0x00cf, 0x00ca, 
	0x00c4, 0x00be, 0x00b8, 0x00b2, 0x00ac, 0x00a7, 0x00a1, 0x009b, 
	0x0095, 0x008f, 0x0089, 0x0082, 0x007c, 0x0076, 0x0070, 0x006a, 
	0x0064, 0x005e, 0x0058, 0x0051, 0x004b, 0x0045, 0x003f, 0x0038, 
	0x0032, 0x002c, 0x0026, 0x001f, 0x0019, 0x0013, 0x000d, 0x0006, 
	0x0000, 0xfffa, 0xfff3, 0xffed, 0xffe7, 0xffe1, 0xffda, 0xffd4, 
	0xffce, 0xffc8, 0xffc1, 0xffbb, 0xffb5, 0xffaf, 0xffa8, 0xffa2, 
	0xff9c, 0xff96, 0xff90, 0xff8a, 0xff84, 0xff7e, 0xff77, 0xff71, 
	0xff6b, 0xff65, 0xff5f, 0xff59, 0xff54, 0xff4e, 0xff48, 0xff42, 
	0xff3c, 0xff36, 0xff31, 0xff2b, 0xff25, 0xff1f, 0xff1a, 0xff14, 
	0xff0f, 0xff09, 0xff04, 0xfefe, 0xfef9, 0xfef3, 0xfeee, 0xfee9, 
	0xfee4, 0xfede, 0xfed9, 0xfed4, 0xfecf, 0xfeca, 0xfec5, 0xfec0, 
	0xfebb, 0xfeb6, 0xfeb2, 0xfead, 0xfea8, 0xfea4, 0xfe9f, 0xfe9a, 
	0xfe00, 0xfe9a, 0xfe9f, 0xfea4, 0xfea8, 0xfead, 0xfeb2, 0xfeb6, 
	0xfebb, 0xfec0, 0xfec5, 0xfeca, 0xfecf, 0xfed4, 0xfed9, 0xfede, 
	0xfee4, 0xfee9, 0xfeee, 0xfef3, 0xfef9, 0xfefe, 0xff04, 0xff09, 
	0xff0f, 0xff14, 0xff1a, 0xff1f, 0xff25, 0xff2b, 0xff31, 0xff36, 
	0xff3c, 0xff42, 0xff48, 0xff4e, 0xff54, 0xff59, 0xff5f, 0xff65, 
	0xff6b, 0xff71, 0xff77, 0xff7e, 0xff84, 0xff8a, 0xff90, 0xff96, 
	0xff9c, 0xffa2, 0xffa8, 0xffaf, 0xffb5, 0xffbb, 0xffc1, 0xffc8, 
	0xffce, 0xffd4, 0xffda, 0xffe1, 0xffe7, 0xffed, 0xfff3, 0xfffa, 
	0x0000, 0x0006, 0x000d, 0x0013, 0x0019, 0x001f, 0x0026, 0x002c, 
	0x0032, 0x0038, 0x003f, 0x0045, 0x004b, 0x0051, 0x0058, 0x005e, 
	0x0064, 0x006a, 0x0070, 0x0076, 0x007c, 0x0082, 0x0089, 0x008f, 
	0x0095, 0x009b, 0x00a1, 0x00a7, 0x00ac, 0x00b2, 0x00b8, 0x00be, 
	0x00c4, 0x00ca, 0x00cf, 0x00d5, 0x00db, 0x00e1, 0x00e6, 0x00ec, 
	0x00f1, 0x00f7, 0x00fc, 0x0102, 0x0107, 0x010d, 0x0112, 0x0117, 
	0x011c, 0x0122, 0x0127, 0x012c, 0x0131, 0x0136, 0x013b, 0x0140, 
	0x0145, 0x014a, 0x014e, 0x0153, 0x0158, 0x015c, 0x0161, 0x0166, 
};
