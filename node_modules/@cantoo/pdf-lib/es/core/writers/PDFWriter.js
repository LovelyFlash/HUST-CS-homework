import { __awaiter } from "tslib";
import PDFCrossRefSection from '../document/PDFCrossRefSection.js';
import PDFHeader from '../document/PDFHeader.js';
import PDFTrailer from '../document/PDFTrailer.js';
import PDFTrailerDict from '../document/PDFTrailerDict.js';
import PDFStream from '../objects/PDFStream.js';
import PDFObjectStream from '../structures/PDFObjectStream.js';
import CharCodes from '../syntax/CharCodes.js';
import { copyStringIntoBuffer, waitForTick } from '../../utils/index.js';
class PDFWriter {
    constructor(context, objectsPerTick) {
        this.parsedObjects = 0;
        this.shouldWaitForTick = (n) => {
            this.parsedObjects += n;
            return this.parsedObjects % this.objectsPerTick === 0;
        };
        this.context = context;
        this.objectsPerTick = objectsPerTick;
    }
    serializeToBuffer() {
        return __awaiter(this, void 0, void 0, function* () {
            const { size, header, indirectObjects, xref, trailerDict, trailer } = yield this.computeBufferSize();
            let offset = 0;
            const buffer = new Uint8Array(size);
            offset += header.copyBytesInto(buffer, offset);
            buffer[offset++] = CharCodes.Newline;
            buffer[offset++] = CharCodes.Newline;
            for (let idx = 0, len = indirectObjects.length; idx < len; idx++) {
                const [ref, object] = indirectObjects[idx];
                const objectNumber = String(ref.objectNumber);
                offset += copyStringIntoBuffer(objectNumber, buffer, offset);
                buffer[offset++] = CharCodes.Space;
                const generationNumber = String(ref.generationNumber);
                offset += copyStringIntoBuffer(generationNumber, buffer, offset);
                buffer[offset++] = CharCodes.Space;
                buffer[offset++] = CharCodes.o;
                buffer[offset++] = CharCodes.b;
                buffer[offset++] = CharCodes.j;
                buffer[offset++] = CharCodes.Newline;
                offset += object.copyBytesInto(buffer, offset);
                buffer[offset++] = CharCodes.Newline;
                buffer[offset++] = CharCodes.e;
                buffer[offset++] = CharCodes.n;
                buffer[offset++] = CharCodes.d;
                buffer[offset++] = CharCodes.o;
                buffer[offset++] = CharCodes.b;
                buffer[offset++] = CharCodes.j;
                buffer[offset++] = CharCodes.Newline;
                buffer[offset++] = CharCodes.Newline;
                const n = object instanceof PDFObjectStream ? object.getObjectsCount() : 1;
                if (this.shouldWaitForTick(n))
                    yield waitForTick();
            }
            if (xref) {
                offset += xref.copyBytesInto(buffer, offset);
                buffer[offset++] = CharCodes.Newline;
            }
            if (trailerDict) {
                offset += trailerDict.copyBytesInto(buffer, offset);
                buffer[offset++] = CharCodes.Newline;
                buffer[offset++] = CharCodes.Newline;
            }
            offset += trailer.copyBytesInto(buffer, offset);
            return buffer;
        });
    }
    computeIndirectObjectSize([ref, object]) {
        const refSize = ref.sizeInBytes() + 3; // 'R' -> 'obj\n'
        const objectSize = object.sizeInBytes() + 9; // '\nendobj\n\n'
        return refSize + objectSize;
    }
    createTrailerDict() {
        return this.context.obj({
            Size: this.context.largestObjectNumber + 1,
            Root: this.context.trailerInfo.Root,
            Encrypt: this.context.trailerInfo.Encrypt,
            Info: this.context.trailerInfo.Info,
            ID: this.context.trailerInfo.ID,
        });
    }
    computeBufferSize() {
        return __awaiter(this, void 0, void 0, function* () {
            const header = PDFHeader.forVersion(1, 7);
            let size = header.sizeInBytes() + 2;
            const xref = PDFCrossRefSection.create();
            const security = this.context.security;
            const indirectObjects = this.context.enumerateIndirectObjects();
            for (let idx = 0, len = indirectObjects.length; idx < len; idx++) {
                const indirectObject = indirectObjects[idx];
                const [ref, object] = indirectObject;
                if (security)
                    this.encrypt(ref, object, security);
                xref.addEntry(ref, size);
                size += this.computeIndirectObjectSize(indirectObject);
                if (this.shouldWaitForTick(1))
                    yield waitForTick();
            }
            const xrefOffset = size;
            size += xref.sizeInBytes() + 1; // '\n'
            const trailerDict = PDFTrailerDict.of(this.createTrailerDict());
            size += trailerDict.sizeInBytes() + 2; // '\n\n'
            const trailer = PDFTrailer.forLastCrossRefSectionOffset(xrefOffset);
            size += trailer.sizeInBytes();
            return { size, header, indirectObjects, xref, trailerDict, trailer };
        });
    }
    encrypt(ref, object, security) {
        if (object instanceof PDFStream) {
            const encryptFn = security.getEncryptFn(ref.objectNumber, ref.generationNumber);
            const unencryptedContents = object.getContents();
            const encryptedContents = encryptFn(unencryptedContents);
            object.updateContents(encryptedContents);
        }
    }
}
PDFWriter.forContext = (context, objectsPerTick) => new PDFWriter(context, objectsPerTick);
export default PDFWriter;
//# sourceMappingURL=PDFWriter.js.map