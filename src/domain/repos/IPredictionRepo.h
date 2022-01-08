#pragma once

#include "ICRUDRepo.h"
#include <entities/Prediction.h>

using IPredictionRepo = ICRUDRepo<PredictionTemplate>;
using IPredictionRepoPtr = std::shared_ptr<IPredictionRepo>;