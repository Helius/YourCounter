#include "PredictionRepoimpl.h"
#include "jsonMappers/PredictionMapper.h"

PredictionRepoImpl::PredictionRepoImpl(const IFirebaseRtDbAPIPtr& api)
    : CrudRepository<PredictionTemplate>("/prediction", api, std::make_shared<PredictionMapper>())
{
}
