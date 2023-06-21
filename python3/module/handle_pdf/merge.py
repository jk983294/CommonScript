import glob2
from pypdf import PdfWriter

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='write pdf')
        parser.add_argument('--dir', '-d', dest="dir", type=str, default='', help='file dir')
        parser.add_argument('--pattern', '-p', dest="pattern", type=str, default='', help='file pattern')
        parser.add_argument('--out', '-o', dest="out", type=str, default='/tmp/merge.pdf', help='out file path')
        args = parser.parse_args()
        return args


    args = parse_args()
    files = []
    if len(args.pattern) > 0:
        print('use pattern |%s|' % args.pattern)
        files = glob2.glob(args.pattern)
    elif len(args.dir) > 0:
        files = glob2.glob(args.dir + "*.pdf")

    if len(files) > 0:
        writer = PdfWriter()
        for pdf in files:
            print("append " + pdf)
            writer.append(pdf)

        with open(args.out, "wb") as f:
            writer.write(f)

        print(args.out + " write end")
    else:
        print("nothing to merge")
