from datetime import datetime
from pypdf import PdfReader, PdfWriter

if __name__ == '__main__':
    def parse_args():
        import argparse
        parser = argparse.ArgumentParser(description='write pdf')
        parser.add_argument('--path', '-p', dest="path", type=str, default='/tmp/test.pdf', help='file path')
        parser.add_argument('--out', '-o', dest="out", type=str, default='/tmp/write.pdf', help='out file path')
        args = parser.parse_args()
        return args


    args = parse_args()
    reader = PdfReader(args.path)
    writer = PdfWriter()

    for page in reader.pages:
        writer.add_page(page)

    meta = reader.metadata
    writer.add_metadata(meta)
    time = datetime.now().strftime(f"%Y%m%d%H%M%S")

    writer.add_metadata(
        {
            "/Author": "Kun",
            "/Producer": "pypdf",
            "/Title": "Copy",
            "/Subject": "Subject",
            "/CreationDate": time,
            "/ModDate": time,
            "/Creator": "Kun",
        }
    )

    with open(args.out, "wb") as f:
        writer.write(f)

    print(args.out + " write end")
