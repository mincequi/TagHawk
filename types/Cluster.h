#ifndef CLUSTER_H
#define CLUSTER_H

#include <cstdint>


using ResourceId = std::uint32_t;

struct Cluster {
    enum Type {
        Album
    };

    Type                    type    = Album;
    bool                    isValid = false;
    std::vector<ResourceId> ids     = {};
};

#endif // CLUSTER_H
