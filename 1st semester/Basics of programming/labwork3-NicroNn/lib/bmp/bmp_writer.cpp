#include "bmp_writer.h"

void SetColor1(unsigned char color[], Colors colors) {
    color[0] = colors.color1[0];
    color[1] = colors.color1[1];
    color[2] = colors.color1[2];
}
void SetColor2(unsigned char color[], Colors colors) {
    color[0] = colors.color2[0];
    color[1] = colors.color2[1];
    color[2] = colors.color2[2];
}
void SetColor3(unsigned char color[], Colors colors) {
    color[0] = colors.color3[0];
    color[1] = colors.color3[1];
    color[2] = colors.color3[2];
}
void SetColor4(unsigned char color[], Colors colors) {
    color[0] = colors.color4[0];
    color[1] = colors.color4[1];
    color[2] = colors.color4[2];
}
void SetColor5(unsigned char color[], Colors colors) {
    color[0] = colors.color5[0];
    color[1] = colors.color5[1];
    color[2] = colors.color5[2];
}


void WriteResultToBmp(const Field& field, const std::string& output_path, uint64_t iteration, Colors colors) {
    int minRow = field.CoordsLimit;
    int maxRow = -1;
    int minCol = field.CoordsLimit;
    int maxCol = -1;

    for (int i = 0; i < field.CoordsLimit; i++) {
        for (int j = 0; j < field.CoordsLimit; j++) {
            if (field.grid[i][j] != 0) {
                minRow = std::min(minRow, i);
                maxRow = std::max(maxRow, i);
                minCol = std::min(minCol, j);
                maxCol = std::max(maxCol, j);
            }
        }
    }

    int newWidth = maxCol - minCol + 1;
    int newHeight = maxRow - minRow + 1;

    std::ofstream image_file;
    image_file.open(output_path + "iteration" + std::to_string(iteration) + ".bmp", std::ios::binary | std::ios::out);

    int rowSize = (newWidth * 3 + 3) & (~3);
    int dataSize = rowSize * newHeight;
    int fileSize = 54 + dataSize;

    unsigned char bmp_file_header[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmp_info_header[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};

    bmp_file_header[2] = (unsigned char) (fileSize);
    bmp_file_header[3] = (unsigned char) (fileSize >> 8);
    bmp_file_header[4] = (unsigned char) (fileSize >> 16);
    bmp_file_header[5] = (unsigned char) (fileSize >> 24);
    bmp_info_header[4] = (unsigned char) (newWidth);
    bmp_info_header[5] = (unsigned char) (newWidth >> 8);
    bmp_info_header[6] = (unsigned char) (newWidth >> 16);
    bmp_info_header[7] = (unsigned char) (newWidth >> 24);
    bmp_info_header[8] = (unsigned char) (newHeight);
    bmp_info_header[9] = (unsigned char) (newHeight >> 8);
    bmp_info_header[10] = (unsigned char) (newHeight >> 16);
    bmp_info_header[11] = (unsigned char) (newHeight >> 24);

    image_file.write(reinterpret_cast<char*>(bmp_file_header), 14);
    image_file.write(reinterpret_cast<char*>(bmp_info_header), 40);

    unsigned char* bmp_data = new unsigned char[dataSize];

    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
            int rowInNewData = i - minRow;
            int colInNewData = j - minCol;
            unsigned char color[3] = {0, 0, 0};

            if (field.grid[i][j] == 0) { // white
                SetColor1(color, colors);
            } else if (field.grid[i][j] == 1) {  // green
                SetColor2(color, colors);
            } else if (field.grid[i][j] == 2) {  // yellow
                SetColor3(color, colors);
            } else if (field.grid[i][j] == 3) {  // purple
                SetColor4(color, colors);
            } else {
                SetColor5(color, colors);
            }

            int dataIndex = (rowInNewData * rowSize + colInNewData * 3);
            bmp_data[dataIndex] = color[2];
            bmp_data[dataIndex + 1] = color[1];
            bmp_data[dataIndex + 2] = color[0];
        }
    }

    image_file.write(reinterpret_cast<char*>(bmp_data), dataSize);

    image_file.close();

    delete[] bmp_data;
}
