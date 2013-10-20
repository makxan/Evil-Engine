
#ifndef SHAPETYPES
#define SHAPETYPES

#include "DrawData.h"
#include "VectorTypes.h"

enum ShapeType {
    NOSHAPE = 0,
	CIRCLE,
    POLYGON
};

/* Shape structure.
 * Stride    : 1
 * ShapeType : 1 * sizeof(float)
 */
typedef struct {
	const enum ShapeType type;
    const float* _padding0;
    const float  _padding1;
    const int    _padding2;
    const float* _padding3;
    const int    _padding4;
} SShape;

/* Cicle struct.
 * Note: Not padded.
 */
typedef struct
{
	const enum ShapeType type;
	Vector2 position;
	float   radius;
} SCircle;

// Polygon datatype.
// TODO: Seperate deformable and non-deformable polygons.
// TODO: Consider adding stride for space efficency.
typedef struct
{
	const enum ShapeType type;
	float*               transShapeToBody; // Transform shape space to body space.
	const float          radius;               // Encasing radius. 
	const int            pointSize;		       // Size of an edge.
	const float*         hullEdges;            // Edges around the polygon in counter clockwise order.
	const int            hullLength;	       // Number of edges in array.
} SPolygon;

#endif
