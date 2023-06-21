from pypdf import PdfReader

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='read pdf')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        args = parser.parse_args()
        return args


    args = parse_args()
    reader = PdfReader(args.path)
    meta = reader.metadata

    print(len(reader.pages))

    print(meta.author)
    print(meta.creator)
    print(meta.producer)
    print(meta.subject)
    print(meta.title)
    print(args.path + " read end")
