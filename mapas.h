#ifndef MAPAS_H
#define MAPAS_H


/* -------------------------------------------MAPAS3D---------------------------------------------------------------- */

const int mapas[5][8][8] = {
    {
        {-1, 0, 0, 0, -1, 0, -1, -1},
        {0, 0, 0, 0, 0, 0, 5, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 6},
        {0, 0, 0, 0, 7, 0, 0, 0},
        {-1, -1, 0, 1, 1, 1, -1, -1}
    },
    {
        {0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, -1, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 2, 2, 0, 0, 0, 3, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 5, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 3, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 4, 0, -1, 7, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, -1, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 2, 2, 0, 0, 3, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {4, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 7, 0},
        {0, 0, 0, 0, 7, 0, 0, 0},
        {0, 6, 0, 1, 1, 1, -1, 0}
    }
};

/* -------------------------------------------MAPAS2D---------------------------------------------------------------- */


const int matrices2d[5][8][8] = {
    {
        {-1, 0, 0, 0, -1, 0, -1, -1},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {-1, -1, 0, 1, 1, 1, -1, -1}
    },
    {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, -1, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, -1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, -1, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0}
    },
    {
        {0, 9, 9, 0, 0, 3, 0, 0},
        {0, 0, 9, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0},
        {4, 0, 0, 9, 0, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 7, 0},
        {0, 0, 0, 0, 7, 0, 0, 0},
        {0, 6, 0, 1, 1, 1, -1, 0}
    }
};



#endif // MAPAS_H