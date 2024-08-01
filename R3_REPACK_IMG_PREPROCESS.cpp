//使用CPP ISO 20，为了使用std::shared_ptr<T[]>与std::format


#include <iostream>
#include<fstream>
#include<string>
#include<Windows.h>


#include"../format_file_path.h"
#include"zlib.h"
#include"zconf.h"
#include"compressonator.h"
#include"opencv2/opencv.hpp"

//includes for 	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
#include "opencv2/core/utils/logger.hpp"

bool recall_func(float, ...);
int aetc(const cv::Mat&,const std::string&,const std::string&);
int afunc(const char* const );
void errlv(const char* const, const int);


struct DDS_PIXELFORMAT {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	DWORD dwRGBBitCount;
	DWORD dwRBitMask;
	DWORD dwGBitMask;
	DWORD dwBBitMask;
	DWORD dwABitMask;
};
typedef struct {
	DWORD			dwIdentify;
	DWORD           dwSize;
	DWORD           dwFlags;
	DWORD           dwHeight;
	DWORD           dwWidth;
	DWORD           dwPitchOrLinearSize;
	DWORD           dwDepth;
	DWORD           dwMipMapCount;
	DWORD           dwReserved1[11];
	DDS_PIXELFORMAT ddspf;
	DWORD           dwCaps;
	DWORD           dwCaps2;
	DWORD           dwCaps3;
	DWORD           dwCaps4;
	DWORD           dwReserved2;
} DDS_HEADER;

namespace {
	constexpr uint8_t colortable[] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
		0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
		0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x02,
		0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
		0x02,0x02,0x02,0x03,0x03,0x03,0x03,0x03,
		0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
		0x03,0x03,0x03,0x03,0x04,0x04,0x04,0x04,
		0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
		0x04,0x04,0x04,0x04,0x04,0x05,0x05,0x05,
		0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,
		0x05,0x05,0x05,0x05,0x05,0x05,0x06,0x06,
		0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
		0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,
		0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
		0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
		0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
		0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
		0x08,0x09,0x09,0x09,0x09,0x09,0x09,0x09,
		0x09,0x09,0x09,0x09,0x09,0x09,0x09,0x09,
		0x09,0x09,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
		0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
		0x0a,0x0a,0x0a,0x0b,0x0b,0x0b,0x0b,0x0b,
		0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,
		0x0b,0x0b,0x0b,0x0b,0x0c,0x0c,0x0c,0x0c,
		0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,
		0x0c,0x0c,0x0c,0x0c,0x0c,0x0d,0x0d,0x0d,
		0x0d,0x0d,0x0d,0x0d,0x0d,0x0d,0x0d,0x0d,
		0x0d,0x0d,0x0d,0x0d,0x0d,0x0d,0x0e,0x0e,
		0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,
		0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0e,0x0f,
		0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f
	};
	uint8_t etcHeader[] = {
		0x44,0x44,0x53,0x20,0x7c,0x00,0x00,0x00,0x07,0x10,0x0a,0x00,0x00,0x04,0x00,0x00,
		0x00,0x04,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x0b,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,
		0x05,0x00,0x00,0x00,0x45,0x54,0x43,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x40,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};
	uint8_t etcHeaderA[] = {
		0x44,0x44,0x53,0x20,0x7c,0x00,0x00,0x00,0x07,0x10,0x02,0x00,0x00,0x02,0x00,0x00,
		0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0a,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,
		0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0xf0,0x00,0x00,
		0x00,0x0f,0x00,0x00,0xf0,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x08,0x10,0x40,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};
	uint8_t atcHeader[] = {
		0x44,0x44,0x53,0x20,0x7c,0x00,0x00,0x00,0x07,0x10,0x0a,0x00,0x00,0x10,0x00,0x00,
		0x00,0x10,0x00,0x00,0x00,0x00,0x80,0x00,0x01,0x00,0x00,0x00,0x0d,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,
		0x04,0x00,0x00,0x00,0x41,0x54,0x43,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x40,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};
	uint8_t atcHeaderA[] = {
		0x44,0x44,0x53,0x20,0x7c,0x00,0x00,0x00,0x07,0x10,0x0a,0x00,0x00,0x10,0x00,0x00,
		0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x0d,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,
		0x04,0x00,0x00,0x00,0x41,0x54,0x43,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x10,0x40,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	};

	uint32_t* const patcHeader = (uint32_t*)atcHeader;
	uint32_t* const petcHeader = (uint32_t*)etcHeader;
	uint32_t* const patcHeaderA = (uint32_t*)atcHeaderA;
	uint32_t* const petcHeaderA = (uint32_t*)etcHeaderA;
}

bool recall_func(float f, ...) {
	return true;
}

int aetc(const cv::Mat & inputImg, const std::string & atcOutName, const std::string& etcOutName) {
	std::vector<cv::Mat> mipmaps;
	std::vector<CMP_Texture> raws, atcs, etcs;
	struct {
		int _w; int _h;
	} mipmap_wh[64] = { 0 };
	//计算MipMaps大小
	auto w = inputImg.cols;
	auto h = inputImg.rows;
	if (w > h) {
		auto* p = mipmap_wh;
		for (int i = h; i >= 1; i /= 2, w /= 2) {
			p->_h = i;
			p->_w = w;
			p++;
		}
	}
	else {
		auto* p = mipmap_wh;
		for (int i = w; i >= 1; i /= 2, h /= 2) {
			p->_h = h;
			p->_w = i;
			p++;
		}
	}
	//创建MipMaps并甩给vector
	{
		//把原图直接甩给vec
		auto const* p = mipmap_wh;
		p++;
		mipmaps.push_back(inputImg);
		//缩小并甩给vector
		while (p->_h != 0) {
			cv::Mat smaller;
			cv::resize(inputImg, smaller, cv::Size{ p->_w,p->_h });
			p++;
			mipmaps.push_back(std::move(smaller));
		}
	}
	//α通道
	bool _4;
	if (inputImg.channels() == 4) {
		_4 = true;
	}
	else {
		_4 = false;
	}
	//状态标签
	bool atcContiue = true;
	bool etcContiue = true;

	CMP_Texture rawTex = { 0 };
	CMP_Texture atcTex = { 0 };
	CMP_Texture etcTex = { 0 };
	rawTex.dwSize = sizeof(rawTex);
	atcTex.dwSize = sizeof(atcTex);
	etcTex.dwSize = sizeof(etcTex);
	if (_4) {
		rawTex.format = CMP_FORMAT_RGBA_8888;
		atcTex.format = CMP_FORMAT_ATC_RGBA_Explicit;
		etcTex.format = CMP_FORMAT_Unknown;
	}
	else {
		rawTex.format = CMP_FORMAT_RGB_888;
		atcTex.format = CMP_FORMAT_ATC_RGB;
		etcTex.format = CMP_FORMAT_ETC_RGB;
	}

	int index;
	index = 0;
	//创建raw合集。
	for (cv::Mat const& img : mipmaps) {
		rawTex.dwWidth = img.cols;
		rawTex.dwHeight = img.rows;
		rawTex.dwPitch = rawTex.dwWidth * (_4 ? 4 : 3);
		rawTex.dwDataSize = CMP_CalculateBufferSize(&rawTex);

		//DEBUG 图像缓冲区大小检查。
		if (_4) {
			assert(rawTex.dwDataSize >= rawTex.dwWidth * rawTex.dwHeight * 4);
		}
		else {
			assert(rawTex.dwDataSize >= rawTex.dwWidth * rawTex.dwHeight * 3);
		}
		// 建立指针
		// 选择手动管理内存
		rawTex.pData = new uint8_t[rawTex.dwDataSize];// _rawpointer.get();

		//复制数据
		if (img.isContinuous()) {
			auto pd = rawTex.pData;
			auto ps = img.data;
			memcpy_s(pd, rawTex.dwDataSize, ps, rawTex.dwDataSize);
		}
		else {
			uint8_t* const pd_c = rawTex.pData;
			uint8_t* pdpos = pd_c;
			const uint8_t* ps = nullptr;
			//rows:H
			for (int i = 0; i != img.rows; ++i) {
				ps = img.ptr<uint8_t>(i);
				memcpy_s(pdpos, -1, ps, img.cols);//没有越界检查
				pdpos += img.cols;
			}
		}
		raws.push_back(rawTex);
		std::cout << std::format("RGB > MipMap {} Created\n", index++);
		//assert(_rawpointer.use_count() == 2);
		rawTex.pData = nullptr;
		//std::shared_ptr<uint8_t[]> _rawpointer 析构一次，指针失效
		//手动管理内存
	}//RAW END

	//ATC
	CMP_CompressOptions atcoptions = { 0 };
	atcoptions.dwSize = sizeof(atcoptions);
	atcoptions.dwnumThreads = 1;
	atcoptions.fquality = 0.10f;
	atcoptions.bDisableMultiThreading = true;

	index = 0;
	for (auto& _rawTex : raws) {
		if (!atcContiue) {
			break;
		}
		//初始化宽高
		atcTex.dwWidth = _rawTex.dwWidth;
		atcTex.dwHeight = _rawTex.dwHeight;
		//atcTex.dwPitch = _rawTex.dwWidth;
		//初始化指针
		atcTex.dwDataSize = CMP_CalculateBufferSize(&atcTex);
		//std::shared_ptr<uint8_t[]> _atcpointer;\
		_atcpointer.reset(new uint8_t[atcTex.dwDataSize]);
		atcTex.pData = new uint8_t[atcTex.dwDataSize];//_atcpointer.get();
		std::cout << std::format("ATC > Compressing Miplevel {}", index);
		CMP_ERROR reValue;
		reValue = CMP_ConvertTexture((&_rawTex), &atcTex, &atcoptions, nullptr);
		if (reValue == CMP_OK) {
			atcs.push_back(atcTex);
			std::cout << std::format("\rATC > Compression succeed with Miplevel {}\n", index++);
		}
		else {
			std::cout << std::format("\rATC > Compression returned an error {} in Miplevel {}\n", (int)reValue, index++);
			atcContiue = false;
		}
	}//ATC END

	//ETC

	CMP_CompressOptions etcoptions = { 0 };
	etcoptions.dwSize = sizeof(etcoptions);
	etcoptions.dwnumThreads = 1;
	etcoptions.fquality = 0.10f;
	etcoptions.bDisableMultiThreading = true;

	index = 0;
	for (auto& _rawTex : raws) {
		if (!etcContiue) {
			break;
		}
		//初始化宽高
		etcTex.dwWidth = _rawTex.dwWidth;
		etcTex.dwHeight = _rawTex.dwHeight;
		//初始化指针
		etcTex.dwDataSize = CMP_CalculateBufferSize(&etcTex);
		if (!_4) {//3通道，调用函数普通压缩
			etcTex.pData = new uint8_t[etcTex.dwDataSize];//_etcpointer.get();
			//转换
			std::cout << std::format("ETC > Compressing Miplevel {}", index);
			CMP_ERROR reValue;
			reValue = CMP_ConvertTexture(&_rawTex, &etcTex, &etcoptions, nullptr);
			if (reValue == CMP_OK) {
#if 0
				//DISCARE
				{
					//std::cout << std::format("\rETC > Fix channel errors in Miplevel {}", index);
					uint64_t* p_u64 = reinterpret_cast<uint64_t*>(etcTex.pData);
					assert(etcTex.dwDataSize % 8 == 0);
					uint32_t len64 = etcTex.dwDataSize / 8;
					for (auto i = 0u; i != len64; ++i) {
						uint8_t* p_u8 = reinterpret_cast<uint8_t*>(p_u64++);
						//交换编码后的R、B
						p_u8[5] ^= p_u8[7];
						p_u8[7] ^= p_u8[5];
						p_u8[5] ^= p_u8[7];
					}
				}
#endif
				etcs.push_back(etcTex);
				std::cout << std::format("\rETC > Compression succeed with Miplevel {}\n", index++);
			}
			else {
				std::cout << std::format("\rETC > Compression returned an error {} in Miplevel{}\n", (int)reValue, index++);
				etcContiue = false;
			}
		}
		else {//4通道，RGBA4444
			etcTex.dwDataSize = etcTex.dwHeight * etcTex.dwWidth * 4 / 2;//RGBA4444, 4 channels & half byte per channel
			etcTex.pData = new uint8_t[etcTex.dwDataSize];//_etcpointer.get();
			assert(etcTex.dwDataSize * 2 == _rawTex.dwDataSize);
			//写数据
			{
				uint8_t* const psrc_begin = _rawTex.pData;
				uint8_t* const psrc_end = _rawTex.pData + _rawTex.dwDataSize;
				uint8_t* psrc_pos;
				uint8_t* pdst_pos = etcTex.pData;
				//rows:H
				for (psrc_pos = psrc_begin; psrc_pos != psrc_end; psrc_pos += 4, pdst_pos += 2) {
					//0x122F->R 11 G 22 B 22 A ff
					//0xRGBA->0xBBGGRRAA
					uint32_t* p_u32 = (uint32_t*)psrc_pos;
					uint16_t* p_u16 = (uint16_t*)pdst_pos;
					uint8_t* p_u8 = (uint8_t*)p_u32;
					*p_u16 = colortable[p_u8[2]];
					*p_u16 <<= 4;
					*p_u16 |= colortable[p_u8[1]];
					*p_u16 <<= 4;
					*p_u16 |= colortable[p_u8[0]];
					*p_u16 <<= 4;
					*p_u16 |= colortable[p_u8[3]];
				}
			}
			etcs.push_back(etcTex);
			std::cout << std::format("ETCA> Compression succeed with Miplevel {}\n", index++);
		}
	}//ETC END

	size_t atcMemFileSize = 128;//dds header 128 bytes
	size_t etcMemFileSize = 128;//dds header 128 bytes

	for (const auto& i : atcs) {
		atcMemFileSize += i.dwDataSize;
	}
	for (const auto& i : etcs) {
		etcMemFileSize += i.dwDataSize;
	}
	uint8_t* const patcMemFile = new uint8_t[atcMemFileSize];
	uint8_t* const petcMemFile = new uint8_t[etcMemFileSize];
	uint8_t* patcMemFilePos = patcMemFile + 128;//skip header
	uint8_t* petcMemFilePos = petcMemFile + 128;//skip header

	{
		//deal with headers
		DDS_HEADER* ph;
		uint32_t* pah, * peh;
		if (_4) {
			pah = patcHeaderA;
			peh = petcHeaderA;
		}
		else {
			pah = patcHeader;
			peh = petcHeader;
		}
		//pah[3] = raws[0].dwHeight; pah[4] = raws[0].dwWidth; pah[7] = raws.size();
		//peh[3] = raws[0].dwHeight; peh[4] = raws[0].dwWidth; peh[7] = raws.size();
		ph = (DDS_HEADER*)pah;

		ph->dwHeight = raws[0].dwHeight;
		ph->dwWidth = raws[0].dwWidth;
		ph->dwPitchOrLinearSize = atcs[0].dwDataSize;

		ph->dwMipMapCount = atcs.size();

		memcpy_s(patcMemFile, 128, pah, 128);

		ph = (DDS_HEADER*)peh;
		ph->dwHeight = raws[0].dwHeight;
		ph->dwWidth = raws[0].dwWidth;
		ph->dwPitchOrLinearSize = etcs[0].dwDataSize;

		ph->dwMipMapCount = etcs.size();
		memcpy_s(petcMemFile, 128, peh, 128);
	}

	//copy main datas & FREE DYNAMIC MEMORY

	mipmaps.clear();

	for (auto& i : raws) {
		if (i.pData)delete[] i.pData;
	}
	raws.clear();

	std::cout << std::format("MAIN> Generating atc.dds image");
	for (auto& i : atcs) {
		if (i.pData)
		{
			memcpy_s(patcMemFilePos, -1, i.pData, i.dwDataSize);
			patcMemFilePos += i.dwDataSize;
			delete[] i.pData;
		}
	}
	std::cout << std::format("\rMAIN> Generated atc.dds image \n");
	atcs.clear();

	std::cout << std::format("MAIN> Generating etc.dds image");
	for (auto& i : etcs) {
		if (i.pData)
		{
			memcpy_s(petcMemFilePos, -1, i.pData, i.dwDataSize);
			petcMemFilePos += i.dwDataSize;
			delete[] i.pData;
		}
	}
	std::cout << std::format("\rMAIN> Generated etc.dds image \n");
	etcs.clear();

	//WRITE DDS FILE
#if 1
	{
		std::ofstream fo;
		fo.open(atcOutName, std::fstream::out | std::fstream::binary);
		if (fo)
		{
			fo.write((char*)patcMemFile, atcMemFileSize);
			fo.close();
			std::cout << std::format("MAIN> Writed act.dds to {}\n", atcOutName);
		}
		else {
			std::cout << std::format("MAIN> Cannot open file {}\n", atcOutName);
		}
		fo.open(etcOutName, std::fstream::out | std::fstream::binary);
		if (fo) {
			fo.write((char*)petcMemFile, etcMemFileSize);
			fo.close();
			std::cout << std::format("MAIN> Writed etc.dds to {}\n", etcOutName);
		}
		else {
			std::cout << std::format("MAIN> Cannot open file {}\n", etcOutName);
		}
	}
#endif
	//COMPRESS WITH ZLIB

	uint8_t* const patcz = new uint8_t[atcMemFileSize * 2];
	uint8_t* const petcz = new uint8_t[etcMemFileSize * 2];
	unsigned long atczSize = atcMemFileSize * 2, etczSize = etcMemFileSize * 2;
	auto reValue_atc = compress2(patcz, &atczSize, patcMemFile, atcMemFileSize, Z_BEST_COMPRESSION);
	std::cout << std::format("ZLIB> Generated atc.dds.z file \n");
	auto reValue_etc = compress2(petcz, &etczSize, petcMemFile, etcMemFileSize, Z_BEST_COMPRESSION);
	std::cout << std::format("ZLIB> Generated etc.dds.z file \n");
	//Write Z file...
	{
		std::ofstream fo;
		fo.open(atcOutName + ".z", std::fstream::out | std::fstream::binary);
		if (fo)
		{
			fo.write((char*)&atcMemFileSize, 4);
			fo.write((char*)patcz, atczSize);
			fo.close();
			std::cout << std::format("MAIN> Writed atc.dds.z to {}.z\n", atcOutName);
		}
		else {
			std::cout << std::format("MAIN> Cannot open file {}.z\n", atcOutName);
		}

		fo.open(etcOutName + ".z", std::fstream::out | std::fstream::binary);
		if (fo)
		{
			fo.write((char*)&etcMemFileSize, 4);
			fo.write((char*)petcz, etczSize);
			fo.close();
			std::cout << std::format("MAIN> Writed etc.dds.z to {}.z\n", etcOutName);
		}
		else {
			std::cout << std::format("MAIN> Cannot open file {}.z\n", etcOutName);
		}
	}
	//Free pointers

	/*
	uint8_t* const patcMemFile = new uint8_t[atcMemFileSize];
	uint8_t* const petcMemFile = new uint8_t[etcMemFileSize];
	uint8_t* const patcz = new uint8_t[atcMemFileSize * 2];
	uint8_t* const petcz = new uint8_t[etcMemFileSize * 2];
	*/
	delete[] patcMemFile;
	delete[] petcMemFile;
	delete[] patcz;
	delete[] petcz;
	return 0;
}
int afunc(const char* const srcimg) {
	using namespace std;

	const string si(srcimg);
	string si_n, si_e;
	string::size_type backslash = si.find_last_of("/\\");
	string::size_type dot = si.find_first_of('.', backslash);
	string so_a, so_e;
	if (dot != string::npos) {
		si_n = si.substr(0, dot);
		if (true) {
			so_a = si_n + ".atc.dds";
			so_e = si_n + ".etc.dds";
		}
	}
	else {
		si_n = si;
		so_a = si_n + ".atc.dds";
		so_e = si_n + ".etc.dds";
	}
	//bool b = (cv::IMREAD_REDUCED_COLOR_2 == CV_8UC4);
	cv::Mat src = cv::imread(si, cv::IMREAD_UNCHANGED);
	if (src.data == nullptr) {
		return -1;
	}

	if (src.channels() == 4) {
		//>248,then remove.
		bool NotAlpha = true;
		for (int i = 0; i != src.rows; ++i) {
			uint8_t* p = src.ptr<uint8_t>(i);
			for (int j = 0; j != src.cols; ++j) {
				if ((p)[3] > 248) {
					continue;
					p += 4;
				}
				else {
					NotAlpha = false;
					goto endloop_alpha;
				}
			}
		}
	endloop_alpha:
		if (NotAlpha) {
			std::cout << std::format("Mat > Alpha of Image {} are all above 0xF8 and has been removed\n",si);
			src = cv::imread(si, cv::IMREAD_COLOR);//相比于拆开再并回去，我觉得这样方便一些
		}
	}
	//重缩放大小，确保是4的倍数并且小于4096x
	cv::Size asize{src.cols,src.rows};
		if (src.cols > 4096) {
			asize.width = 4096;
			std::cout << std::format("Mat > Size of {} is toooo big to encode. Resized width to 4096\n",si);
		}
		if (src.rows > 4096) {
			asize.height = 4096;
			std::cout << std::format("Mat > Size of {} is tooo big to encode. Resized height to 4096\n",si);
		}
	if (src.cols % 4 != 0 ) {
		asize.width = ((src.cols + 3) / 4) * 4;
		std::cout << std::format("Mat > Size of {} MUST be divisible by 4. Resized width to {}\n", si,asize.width);
	}
	if (src.rows % 4 != 0) {
		asize.height = ((src.rows + 3) / 4) * 4;
		std::cout << std::format("Mat > Size of {} MUST be divisible by 4. Resized height to {}\n", si,asize.height);
	}
	if (asize.width != src.cols || asize.height != src.rows) {
		cv::resize(src,src,asize);//cv::resize(inputImg, smaller, cv::Size{ p->_w,p->_h });
	}

	cv::flip(src, src, 0);

	aetc(src, so_a, so_e);

	return 0;
}

void errlv(const char* const c, const int e = 0) {
	using namespace std;
	if (e == 0)return;
	return;
}

int main(int c, char** v)
{

	//WIN32_FIND_DATAA data;
	using namespace std;
	std::cout << "Hello World!\n";
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	if (c > 1) {

		for (int i = 1; i != c; ++i) {
			errlv(v[i], afunc(v[i]));
		}
	}
	else {
		string sname;
		cin >> sname;
		format_file_path(sname);
		errlv(sname.c_str(), afunc(sname.c_str()));
	}
}

