from pypdf import PdfReader, PdfWriter

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='rotate pdf')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        parser.add_argument('--num', '-n', dest="num", type=int, default='0', help='which page to rotate')
        parser.add_argument('--out', '-o', dest="out", type=str, default='/tmp/rotate.pdf', help='out file path')
        args = parser.parse_args()
        return args


    args = parse_args()
    reader = PdfReader(args.path)
    writer = PdfWriter()

    p_idx = 0
    for page in reader.pages:
        writer.add_page(page)
        if p_idx == args.num:
            writer.pages[p_idx].rotate(90)
        p_idx += 1

    with open(args.out, "wb") as f:
        writer.write(f)

    print(args.out + " write rotate end")
