#pragma once

template <typename T>
struct IJsonMapper {
    virtual T fromJson(const QString & id, const QJsonObject & json) = 0;
    virtual QJsonObject toJson(const T & t) = 0;
    virtual void patch(T & t, const QJsonObject & json) = 0;
    virtual QJsonObject diff(const T & from, const T & to) = 0;
    virtual ~IJsonMapper() = default;
};
