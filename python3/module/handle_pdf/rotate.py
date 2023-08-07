import os

from pypdf import PdfReader, PdfWriter

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='rotate pdf')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        parser.add_argument('--num', '-n', dest="num", type=int, default='0', help='which page to rotate')
        parser.add_argument('--out', '-o', dest="out", type=str, default='', help='out file path')
        parser.add_argument('--type', '-t', dest="type", type=int, default='0', help='type to rotate')
        args = parser.parse_args()
        return args


    args = parse_args()
    reader = PdfReader(args.path)
    writer = PdfWriter()

    dir_ = os.path.dirname(args.path)
    out_path = os.path.join(dir_, "rotate.pdf")
    if len(args.out) > 0:
        out_path = args.out

    p_idx = 0
    for page in reader.pages:
        writer.add_page(page)
        if args.type == 0:
            writer.pages[p_idx].rotate(180)
        elif args.type == 1:
            if p_idx % 2 == 0:  
                writer.pages[p_idx].rotate(180)
        elif args.type == 2:
            if p_idx % 2 == 1:
                writer.pages[p_idx].rotate(180)
        p_idx += 1

    with open(out_path, "wb") as f:
        writer.write(f)

    print(out_path + " write rotate end")
