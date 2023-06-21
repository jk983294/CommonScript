from pypdf import PdfReader, PdfWriter

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='split pdf')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        parser.add_argument('--num', '-n', dest="num", type=int, default='2', help='num to split')
        args = parser.parse_args()
        return args


    def chunks(lst, n):
        """Yield successive n-sized chunks from lst."""
        for i in range(0, len(lst), n):
            yield lst[i:i + n]


    args = parse_args()
    reader = PdfReader(args.path)
    len_ = len(reader.pages)

    p_prefix = args.path[:-4]
    p_num = len_ // args.num
    split_idx = 0
    for l in chunks(range(len_), p_num if len_ % args.num == 0 else p_num + 1):
        print(l)
        writer = PdfWriter()
        for idx in l:
            writer.add_page(reader.pages[idx])

        file_o = p_prefix + '.' + str(split_idx) + ".pdf"
        with open(file_o, "wb") as f:
            writer.write(f)
            print("write " + file_o)

        split_idx += 1
