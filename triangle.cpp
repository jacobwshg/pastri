#include <iostream>
#include <cstddef>
#include <vector>
#include <sstream>

struct Row
{
    std::vector<std::size_t> data;
    std::size_t str_len;

    std::size_t &operator[](std::size_t);
};

std::size_t &
Row::operator[](std::size_t colno)
{
    return data[colno];
}

struct Triangle
{
    std::size_t height;
    std::vector<Row> rows;

    Triangle(std::size_t);

    std::string str(void);
};

Triangle::Triangle(std::size_t height) :
    height {height}, rows {height}
{
    for (std::size_t rowno {0}; rowno < height; ++rowno)
    {
        Row &row = rows[rowno];
        row.data.reserve(rowno + 1);
        for (std::size_t colno {0}; colno <= rowno; ++colno)
        {
            row[colno] =
                (rowno == 0 || colno == 0 || colno == rowno) ?
                1 :
                rows[rowno - 1][colno - 1] + rows[rowno - 1][colno];
            row.str_len += std::to_string(row[colno]).size();
        }
        row.str_len += rowno;
    }
}

std::string
Triangle::str(void)
{
    std::ostringstream oss {};
    Row &base_row = rows[height - 1];
    for (std::size_t rowno {0}; rowno < height; ++rowno)
    {
        Row &row = rows[rowno];

        // Pad on the left for centering
        std::size_t pad_len 
        {
            (base_row.str_len - row.str_len) / 2
        };
        for (std::size_t i = 0; i < pad_len; ++i)
        {
            oss << " ";
        }

        // Add elements
        for (std::size_t colno {0}; colno <= rowno; ++colno)
        {
            oss << row[colno];
            oss << (colno == rowno ? "\n" : " ");
        }
    }
    return oss.str();
}

int 
main()
{
    Triangle t {15};
    std::cout << t.str();
    return 0;
}

