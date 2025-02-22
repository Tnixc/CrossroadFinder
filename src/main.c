#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
#include <time.h>

#include "fortressgenerator/FortressGenerator.h"
#include "util/Inputs.h"

typedef enum {
    DOUBLE = 0,
    TRIPLE_LINE = 1,
    QUAD_LINE = 2,
    QUINT_LINE = 3,
    TRIPLE_CORNER = 4,
    QUAD_SQUARE = 5,
    QUINT_BLOB = 6
} CrossroadShape;

const char *SHAPE_NAMES[] = {
    "DOUBLE",
    "TRIPLE_LINE",
    "QUAD_LINE",
    "QUINT_LINE",
    "TRIPLE_CORNER",
    "QUAD_SQUARE",
    "QUINT_BLOB"
};

#define SHAPE_COUNT (sizeof(SHAPE_NAMES) / sizeof(SHAPE_NAMES[0]))

typedef struct {
    int32_t x;
    int32_t z;
} Offset;

typedef struct {
    Offset *offsets;
} Shape;

typedef struct {
    Shape *shapes;
    int offsetsCount;
    int shapesCount;
} ShapeVariants;

Offset DOUBLE_X_OFFSETS[] = {
    { 19, 0 }
};

Offset DOUBLE_Z_OFFSETS[] = {
    { 0, 19 }
};

Shape DOUBLE_SHAPES[] = {
    { DOUBLE_X_OFFSETS },
    { DOUBLE_Z_OFFSETS }
};

Offset TRIPLE_LINE_X_OFFSETS[] = {
    { 19, 0 },
    { 38, 0 }
};

Offset TRIPLE_LINE_Z_OFFSETS[] = {
    { 0, 19 },
    { 0, 38 }
};

Shape TRIPLE_LINE_SHAPES[] = {
    { TRIPLE_LINE_X_OFFSETS },
    { TRIPLE_LINE_Z_OFFSETS }
};

Offset QUAD_LINE_X_OFFSETS[] = {
    { 19, 0 },
    { 38, 0 },
    { 57, 0 }
};

Offset QUAD_LINE_Z_OFFSETS[] = {
    { 0, 19 },
    { 0, 38 },
    { 0, 57 }
};

Shape QUAD_LINE_SHAPES[] = {
    { QUAD_LINE_X_OFFSETS },
    { QUAD_LINE_Z_OFFSETS }
};

Offset QUINT_LINE_X_OFFSETS[] = {
    { 19, 0 },
    { 38, 0 },
    { 57, 0 },
    { 76, 0 }
};

Offset QUINT_LINE_Z_OFFSETS[] = {
    { 0, 19 },
    { 0, 38 },
    { 0, 57 },
    { 0, 76 }
};

Shape QUINT_LINE_SHAPES[] = {
    { QUINT_LINE_X_OFFSETS },
    { QUINT_LINE_Z_OFFSETS }
};

Offset TRIPLE_CORNER_NN_OFFSETS[] = {
    { 19, 0 },
    { 19, -19 }
};

Offset TRIPLE_CORNER_NP_OFFSETS[] = {
    { 19, 0 },
    { 19, 19 }
};

Offset TRIPLE_CORNER_PP_OFFSETS[] = {
    { 19, 0 },
    { 0, 19 }
};

Offset TRIPLE_CORNER_PN_OFFSETS[] = {
    { 0, 19 },
    { 19, 19 }
};

Shape TRIPLE_CORNER_SHAPES[] = {
    { TRIPLE_CORNER_NN_OFFSETS },
    { TRIPLE_CORNER_NP_OFFSETS },
    { TRIPLE_CORNER_PP_OFFSETS },
    { TRIPLE_CORNER_PN_OFFSETS }
};

Offset QUAD_SQUARE_OFFSETS[] = {
    { 0, 19 },
    { 19, 0 },
    { 19, 19 }
};

Shape QUAD_SQUARE_SHAPES[] = {
    { QUAD_SQUARE_OFFSETS }
};

Offset QUINT_BLOB_0_OFFSETS[] = {
    { 0, 19 },
    { 0, 38 },
    { 19, 19 },
    { 19, 38 }
};

Offset QUINT_BLOB_1_OFFSETS[] = {
    { 0, 19 },
    { 19, -19 },
    { 19, 0 },
    { 19, 19 }
};

Offset QUINT_BLOB_2_OFFSETS[] = {
    { 0, 19 },
    { 19, 0 },
    { 19, 19 },
    { 38, 0 }
};

Offset QUINT_BLOB_3_OFFSETS[] = {
    { 0, 19 },
    { 19, 0 },
    { 19, 19 },
    { 38, 19 }
};

Offset QUINT_BLOB_4_OFFSETS[] = {
    { 0, 19 },
    { 19, 0 },
    { 19, 19 },
    { 19, 38 }
};

Offset QUINT_BLOB_5_OFFSETS[] = {
    { 0, 19 },
    { 0, 38 },
    { 19, 0 },
    { 19, 19 }
};

Offset QUINT_BLOB_6_OFFSETS[] = {
    { 19, 0 },
    { 19, -19 },
    { 38, 0 },
    { 38, -19 }
};

Offset QUINT_BLOB_7_OFFSETS[] = {
    { 19, 0 },
    { 19, 19 },
    { 38, 0 },
    { 38, 19 }
};

Shape QUINT_BLOB_SHAPES[] = {
    { QUINT_BLOB_0_OFFSETS },
    { QUINT_BLOB_1_OFFSETS },
    { QUINT_BLOB_2_OFFSETS },
    { QUINT_BLOB_3_OFFSETS },
    { QUINT_BLOB_4_OFFSETS },
    { QUINT_BLOB_5_OFFSETS },
    { QUINT_BLOB_6_OFFSETS },
    { QUINT_BLOB_7_OFFSETS },
};

ShapeVariants SHAPES[] = {
    { DOUBLE_SHAPES, 1, 2 },
    { TRIPLE_LINE_SHAPES, 2, 2 },
    { QUAD_LINE_SHAPES, 3, 2 },
    { QUINT_LINE_SHAPES, 4, 2 },
    { TRIPLE_CORNER_SHAPES, 2, 4 },
    { QUAD_SQUARE_SHAPES, 3, 1 },
    { QUINT_BLOB_SHAPES, 4, 8 }
};

typedef struct {
    Version version;
    int64_t structureSeed;
    int32_t salt;
    CrossroadShape crossroadShape;
    int32_t maxY;
    int32_t searchRadius;
    int32_t searchCenterX;
    int32_t searchCenterZ;
} InputData;

void processRegion(InputData *inputData, FortressGenerator *fortressGenerator, int32_t regionX, int32_t regionZ) {
    fortressGenerator_generateForRegion(fortressGenerator, inputData->structureSeed, regionX, regionZ, inputData->salt, inputData->version);
    if (fortressGenerator->piecesCount == 0) return;

    BlockBox *crossroadsByHeight[5][5];
    int crossroadCounts[5] = { 0 };
    int height[5];
    int heightCount = 0;

    Piece *lastPiece = fortressGenerator->pieces + fortressGenerator->piecesCount - 1;
    for (Piece *piece = fortressGenerator->pieces; piece <= lastPiece; piece++) {
        if (piece->pieceType == BRIDGE_CROSSING && piece->boundingBox.minY <= inputData->maxY) {
            int i;
            for (i = 0; i < heightCount; i++) {
                if (height[i] == piece->boundingBox.minY) {
                    break;
                }
            }
            crossroadsByHeight[i][crossroadCounts[i]++] = &(piece->boundingBox);
            height[i] = piece->boundingBox.minY;
            if (i == heightCount) heightCount++;
        }
    }

    ShapeVariants *shapeVariants = &(SHAPES[inputData->crossroadShape]);

    FILE *logFile = fopen("output.log", "a"); // Open the log file in append mode
    if (logFile == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    for (int heightId = 0; heightId < heightCount; heightId++) {
        int crossroadCount = crossroadCounts[heightId];
        if(crossroadCount <= shapeVariants->offsetsCount) continue;
        
        BlockBox **crossroads = crossroadsByHeight[heightId];

        for (int mainId = 0; mainId < crossroadCount; mainId++) {
            BlockBox *mainBox = crossroads[mainId];
            for (int shapeId = 0; shapeId < shapeVariants->shapesCount; shapeId++) {
                Shape *shape = &(shapeVariants->shapes[shapeId]);
                int good = 0;
                for (int otherId = 0; otherId < crossroadCount; otherId++) {
                    if (otherId == mainId) continue;

                    BlockBox *otherBox = crossroads[otherId];
                    int32_t offsetX = otherBox->minX - mainBox->minX;
                    int32_t offsetZ = otherBox->minZ - mainBox->minZ;
                    if ((offsetX % 19) != 0 || (offsetZ % 19) != 0) continue;

                    for (int offsetId = 0; offsetId < shapeVariants->offsetsCount; offsetId++) {
                        if (offsetX == shape->offsets[offsetId].x && offsetZ == shape->offsets[offsetId].z) {
                            good++;
                            break;
                        }
                    }
                }
                if (good >= shapeVariants->offsetsCount) {
                    // printf("Found a good shape at /tp %i %i %i\n", mainBox->minX, mainBox->minY, mainBox->minZ);
                    fprintf(logFile, "%i %i\n", mainBox->minX, mainBox->minZ);
                    fclose(logFile); // Close the file after writing
                    return;
                }
            }
        }
    }
   fclose(logFile); // Close the file if no output was written
}

bool getInputData(InputData *inputData) {
    if (!getIntEnum("closest lower version", (int*)&inputData->version, VERSION_NAMES, VERSION_COUNT)) {
        return 0;
    }

    if (!getI64Number("numeric world seed", &inputData->structureSeed, false, 0, INT64_MIN, INT64_MAX)) {
        return 0;
    }

    if (inputData->version >= v1_16_1) {
        if (!getI32Number("fortress salt", &inputData->salt, true, FORTRESS_SALT, INT32_MIN, INT32_MAX)) {
            return 0;
        }
    }

    if (!getIntEnum("crossroad shape", (int*)&inputData->crossroadShape, SHAPE_NAMES, SHAPE_COUNT)) {
        return 0;
    }

    if (!getI32Number("maxY", &inputData->maxY, true, 255, 48, INT32_MAX)) {
        return 0;
    }
    
    if (!getI32Number("search radius", &inputData->searchRadius, false, 0, 0, 60000000)) {
        return 0;
    }

    if (!getI32Number("search center X", &inputData->searchCenterX, true, 0, -30000000, 30000000)) {
        return 0;
    }
    
    if (!getI32Number("search center Z", &inputData->searchCenterZ, true, 0, -30000000, 30000000)) {
        return 0;
    }

    return 1;
}

int main() {
    InputData inputData;

    if (getInputData(&inputData)) {
        FortressGenerator fortressGenerator;

        int32_t regionSize = fortressGenerator_getRegionSize(inputData.version);

        int32_t regionRadius = inputData.searchRadius / regionSize / 16 + 1;
        int32_t regionCenterX = inputData.searchCenterX / regionSize / 16;
        int32_t regionCenterZ = inputData.searchCenterZ / regionSize / 16;

        int32_t regionMinX = regionCenterX - regionRadius;
        int32_t regionMaxX = regionCenterX + regionRadius;
        int32_t regionMinZ = regionCenterZ - regionRadius;
        int32_t regionMaxZ = regionCenterZ + regionRadius;

        for(int32_t regionX = regionMinX; regionX <= regionMaxX; regionX++) {
            for(int32_t regionZ = regionMinZ; regionZ <= regionMaxZ; regionZ++) {
                processRegion(&inputData, &fortressGenerator, regionX, regionZ);
            }
        }
    }

    printf("Press enter to continue . . .\n");
    getchar();

    return 0;
}
