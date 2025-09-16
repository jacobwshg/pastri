class Row:
    def __init__(self, rowno):
        # Preallcate row cells
        self.data = [0 for _ in range(rowno + 1)]
        nspaces = rowno
        self.str_len = nspaces

class Triangle:
    def __init__(self, height):
        self.height = height
        self.rows = [Row(rowno) for rowno in range(height)]
        for rowno in range(height):
            for colno in range(rowno + 1):
                row_cur = self.rows[rowno]
                row_cur.data[colno] =\
                    1 if rowno == 0 or colno == 0 or colno == rowno\
                      else sum(self.rows[rowno - 1].data[colno - 1:colno + 1])
                row_cur.str_len += len(str(row_cur.data[colno]))

    def __str__(self):
        t_str = ''
        base_str_len = self.rows[self.height - 1].str_len
        for rowno in range(self.height):
            row_cur = self.rows[rowno]
            pad_len = (base_str_len - row_cur.str_len) // 2
            t_str += ' ' * pad_len
            for colno in range(rowno + 1):
                t_str += str(row_cur.data[colno])
                t_str += ' ' if colno < rowno else '\n'

        return t_str

if __name__ == '__main__':
    height = input('Enter height: ')
    t = Triangle(int(height))
    print(str(t))

__all__ = [\
  'Triangle',\
]

