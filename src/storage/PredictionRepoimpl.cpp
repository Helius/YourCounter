#include "PredictionRepoimpl.h"
#include "jsonMappers/PredictionMapper.h"

PredictionRepoImpl::PredictionRepoImpl(const IFirebaseRtDbAPIPtr& api)
    : CrudRepository<Prediction>("/prediction", api, std::make_shared<PredictionMapper>())
{
}
