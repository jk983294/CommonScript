from pypdf import PdfReader

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='write txt')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        parser.add_argument('--out', '-o', dest="out", type=str, default='/tmp/write.txt', help='out file path')
        args = parser.parse_args()
        return args


    args = parse_args()
    reader = PdfReader(args.path)
    with open(args.out, "wt") as f:
        for page in reader.pages:
            text = page.extract_text()
            f.write(text)
            f.write("\n")

    print(args.out + " write end")
