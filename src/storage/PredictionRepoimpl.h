#pragma once

#include "CrudRepoImpl.h"
#include "IFirebaseRtDbApi.h"
#include <entities/Prediction.h>

class PredictionRepoImpl : public CrudRepository<Prediction> {
public:
    PredictionRepoImpl(const IFirebaseRtDbAPIPtr& api);
};
