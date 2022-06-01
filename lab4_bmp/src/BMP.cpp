#include "../inc/BMP.h"
#include <cmath>

using std::cos;
using std::sin;
using std::acos;

namespace mt {
    namespace images {

        BMP::BMP() {
            m_width = 0;
            m_height = 0;
            BMPHEADER bmpHeader_new;
            bmpHeader_new.Type = 0x4D42; //   BMP
            bmpHeader_new.Size = 14 + 40 + (3 * m_width * m_height);
            if (m_width % 4 != 0)
                bmpHeader_new.Size += (4 - (3 * m_width) % 4) * m_height;
            bmpHeader_new.OffBits = 54;
            bmpHeader_new.Reserved1 = 0;
            bmpHeader_new.Reserved2 = 0;

            m_header = bmpHeader_new;

            BMPINFO bmpInfo_new;
            bmpInfo_new.BitCount = 24;
            bmpInfo_new.ClrImportant = 0;
            bmpInfo_new.ClrUsed = 0;
            bmpInfo_new.Compression = 0;
            bmpInfo_new.Height = m_height;
            bmpInfo_new.Planes = 1;
            bmpInfo_new.Size = 40;
            bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
            bmpInfo_new.Width = m_width;
            bmpInfo_new.XPelsPerMeter = 0;
            bmpInfo_new.YPelsPerMeter = 0;

            m_info = bmpInfo_new;
        }

        BMP::BMP(int width, int height) {
            m_width = width;
            m_height = height;
            m_pixels = new Pixel *[m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = {0, 0, 0};


            BMPHEADER bmpHeader_new;
            bmpHeader_new.Type = 0x4D42; //   BMP
            bmpHeader_new.Size = 14 + 40 + (3 * m_width * m_height);
            if (m_width % 4 != 0)
                bmpHeader_new.Size += (4 - (3 * m_width) % 4) * m_height;
            bmpHeader_new.OffBits = 54;
            bmpHeader_new.Reserved1 = 0;
            bmpHeader_new.Reserved2 = 0;

            m_header = bmpHeader_new;

            BMPINFO bmpInfo_new;
            bmpInfo_new.BitCount = 24;
            bmpInfo_new.ClrImportant = 0;
            bmpInfo_new.ClrUsed = 0;
            bmpInfo_new.Compression = 0;
            bmpInfo_new.Height = m_height;
            bmpInfo_new.Planes = 1;
            bmpInfo_new.Size = 40;
            bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
            bmpInfo_new.Width = m_width;
            bmpInfo_new.XPelsPerMeter = 0;
            bmpInfo_new.YPelsPerMeter = 0;

            m_info = bmpInfo_new;
        }

        BMP::BMP(const BMP &bmp) {
            if (m_pixels != nullptr) {
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            m_width = bmp.m_width;
            m_height = bmp.m_height;

            m_pixels = new Pixel *[m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = bmp.m_pixels[i][j];
        }

        BMP &BMP::operator=(const BMP &bmp) {
            if (m_pixels != nullptr) {
                for (int i = 0; i < m_height; i++)
                    delete[] m_pixels[i];
                delete[] m_pixels;
            }

            m_width = bmp.m_width;
            m_height = bmp.m_height;

            m_pixels = new Pixel *[m_height];
            for (int i = 0; i < m_height; i++)
                m_pixels[i] = new Pixel[m_width];

            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++)
                    m_pixels[i][j] = bmp.m_pixels[i][j];

            return *this;
        }

        BMP::~BMP() {
            for (int i = 0; i < m_height; i++)
                delete[] m_pixels[i];
            delete[] m_pixels;
        }

        bool equalPixel(Pixel &a, Pixel &b) {
            return (a.r == b.r and a.b == b.b and a.g == b.g);
        }

        void BMP::Fill(Pixel pixel) {
            for (int i = 0; i < m_height; i++){
                for (int j = 0; i < m_width; j++){
                    m_pixels[i][j] = pixel;
                }
            }
        }

        void BMP::Code(Pixel pixel) {
            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++) {
                    Pixel p_m = m_pixels[i][j];
                    if (not equalPixel(p_m, pixel)) {
                        m_pixels[i][j] = Pixel({pixel.r, static_cast<unsigned char>(pixel.g - 1), pixel.b});
                    }
                }
        }

        void BMP::Uncode(Pixel pixel) {
            for (int i = 0; i < m_height; i++)
                for (int j = 0; j < m_width; j++) {
                    Pixel p = m_pixels[i][j];
                    if (not equalPixel(p, pixel)) {
                        m_pixels[i][j] = Pixel({0, 255, 0});
                    }
                }
        }

        void BMP::Open(const std::string &filename) {
            std::ifstream in(filename, std::ios::binary);

            if (!in.is_open())
                throw std::exception();

            // Считать 14 байтов побайтово и заполнить структуру BMPHEADER
            in.read(reinterpret_cast<char *>(&m_header), sizeof(BMPHEADER));


            in.read(reinterpret_cast<char *>(&m_info), sizeof(BMPINFO));

            m_pixels = new Pixel *[m_info.Height];
            m_height = m_info.Height;
            m_width = m_info.Width;
            for (int i = 0; i < m_info.Height; i++)
                m_pixels[i] = new Pixel[m_info.Width];

            for (int i = 0; i < m_info.Height; i++) {
                for (int j = 0; j < m_info.Width; j++)
                    in.read(reinterpret_cast<char *>(&m_pixels[i][j]), sizeof(Pixel));

                if ((3 * m_info.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3 * m_info.Width) % 4; j++) {
                        char c;
                        in.read(&c, 1);
                    }
            }
        }

        void BMP::Save(const std::string &filename) {
            if (m_width == 0 || m_height == 0)
                throw std::exception();

            //
            std::ofstream out(filename, std::ios::binary);

            out.write(reinterpret_cast<char *>(&m_header), sizeof(BMPHEADER));

            out.write(reinterpret_cast<char *>(&m_info), sizeof(BMPINFO));

            // Записать пиксели
            for (int i = 0; i < m_info.Height; i++) {
                for (int j = 0; j < m_info.Width; j++)
                    out.write(reinterpret_cast<char *>(&m_pixels[i][j]), sizeof(Pixel));

                if ((3 * m_info.Width) % 4 != 0)
                    for (int j = 0; j < 4 - (3 * m_info.Width) % 4; j++) {
                        char c = 0;
                        out.write(&c, 1);
                    }
            }
            out.close();
        }

    }
}

