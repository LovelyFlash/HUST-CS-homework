import { __awaiter } from "tslib";
import PDFHeader from '../document/PDFHeader.js';
import PDFTrailer from '../document/PDFTrailer.js';
import PDFInvalidObject from '../objects/PDFInvalidObject.js';
import PDFName from '../objects/PDFName.js';
import PDFNumber from '../objects/PDFNumber.js';
import PDFRef from '../objects/PDFRef.js';
import PDFStream from '../objects/PDFStream.js';
import PDFCatalog from '../structures/PDFCatalog.js';
import PDFPageTree from '../structures/PDFPageTree.js';
import PDFPageLeaf from '../structures/PDFPageLeaf.js';
import PDFCrossRefStream from '../structures/PDFCrossRefStream.js';
import PDFObjectStream from '../structures/PDFObjectStream.js';
import PDFWriter from './PDFWriter.js';
import { last, waitForTick } from '../../utils/index.js';
class PDFStreamWriter extends PDFWriter {
    constructor(context, objectsPerTick, encodeStreams, objectsPerStream) {
        super(context, objectsPerTick);
        this.encodeStreams = encodeStreams;
        this.objectsPerStream = objectsPerStream;
    }
    computeBufferSize() {
        return __awaiter(this, void 0, void 0, function* () {
            let objectNumber = this.context.largestObjectNumber + 1;
            const header = PDFHeader.forVersion(1, 7);
            let size = header.sizeInBytes() + 2;
            const xrefStream = PDFCrossRefStream.create(this.createTrailerDict(), this.encodeStreams);
            const uncompressedObjects = [];
            const compressedObjects = [];
            const objectStreamRefs = [];
            const security = this.context.security;
            const indirectObjects = this.context.enumerateIndirectObjects();
            for (let idx = 0, len = indirectObjects.length; idx < len; idx++) {
                const indirectObject = indirectObjects[idx];
                const [ref, object] = indirectObject;
                const shouldNotCompress = ref === this.context.trailerInfo.Encrypt ||
                    object instanceof PDFStream ||
                    object instanceof PDFInvalidObject ||
                    object instanceof PDFCatalog ||
                    object instanceof PDFPageTree ||
                    object instanceof PDFPageLeaf ||
                    ref.generationNumber !== 0;
                if (shouldNotCompress) {
                    uncompressedObjects.push(indirectObject);
                    if (security)
                        this.encrypt(ref, object, security);
                    xrefStream.addUncompressedEntry(ref, size);
                    size += this.computeIndirectObjectSize(indirectObject);
                    if (this.shouldWaitForTick(1))
                        yield waitForTick();
                }
                else {
                    let chunk = last(compressedObjects);
                    let objectStreamRef = last(objectStreamRefs);
                    if (!chunk || chunk.length % this.objectsPerStream === 0) {
                        chunk = [];
                        compressedObjects.push(chunk);
                        objectStreamRef = PDFRef.of(objectNumber++);
                        objectStreamRefs.push(objectStreamRef);
                    }
                    xrefStream.addCompressedEntry(ref, objectStreamRef, chunk.length);
                    chunk.push(indirectObject);
                }
            }
            for (let idx = 0, len = compressedObjects.length; idx < len; idx++) {
                const chunk = compressedObjects[idx];
                const ref = objectStreamRefs[idx];
                const objectStream = PDFObjectStream.withContextAndObjects(this.context, chunk, this.encodeStreams);
                if (security)
                    this.encrypt(ref, objectStream, security);
                xrefStream.addUncompressedEntry(ref, size);
                size += this.computeIndirectObjectSize([ref, objectStream]);
                uncompressedObjects.push([ref, objectStream]);
                if (this.shouldWaitForTick(chunk.length))
                    yield waitForTick();
            }
            const xrefStreamRef = PDFRef.of(objectNumber++);
            xrefStream.dict.set(PDFName.of('Size'), PDFNumber.of(objectNumber));
            xrefStream.addUncompressedEntry(xrefStreamRef, size);
            const xrefOffset = size;
            size += this.computeIndirectObjectSize([xrefStreamRef, xrefStream]);
            uncompressedObjects.push([xrefStreamRef, xrefStream]);
            const trailer = PDFTrailer.forLastCrossRefSectionOffset(xrefOffset);
            size += trailer.sizeInBytes();
            return { size, header, indirectObjects: uncompressedObjects, trailer };
        });
    }
}
PDFStreamWriter.forContext = (context, objectsPerTick, encodeStreams = true, objectsPerStream = 50) => new PDFStreamWriter(context, objectsPerTick, encodeStreams, objectsPerStream);
export default PDFStreamWriter;
//# sourceMappingURL=PDFStreamWriter.js.map