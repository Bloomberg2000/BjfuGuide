//
// Created by 庞博 on 2018-12-19.
//

#pragma once
#ifndef BJFU_TOUR_GUIDE_BACKGROUNDCONTROLLER_H
#define BJFU_TOUR_GUIDE_BACKGROUNDCONTROLLER_H

#include "../Library/GraphMatrix.h"
#include "../Library/Vector.h"
#include "../Library/Stack.h"
#include "../DataModel/ScenicSpot.h"
#include "../DataModel/TourRoute.h"
#include "../Util/StatusType.h"
#include "../Util/ReturnType.h"
#include "../Util/UWPHelper.h"

class MapService {
private:
    Structure::GraphMatrix<ScenicSpot, TourRoute> _bjfuMap;
    MapServiceStatus CurrentStatus;

public:
    MapService();

    virtual ~MapService();

    MapServiceStatus getCurrentStatus() const;

// 前台服务
    Structure::Vector<ScenicSpot> getSpotInfoByName(const Structure::String &spotName);

    Structure::Vector<ScenicSpot> getSpotListByFunction(const Structure::String &function);

    Structure::Stack<ScenicSpot> getShortestPath(const Structure::String &firstPointName,
                                                 const Structure::String &secondPointName,
                                                 int &shortestLength);

    Structure::Vector<Structure::Stack<ScenicSpot>> getAllPath(const Structure::String &firstPointName,
                                                               const Structure::String &secondPointName);

// 后台管理
	const Structure::Vector<Structure::Vertex<ScenicSpot>> &getV() const {
		return _bjfuMap.getV();
	}

	const Structure::Vector<Structure::Vector<Structure::Edge<TourRoute> *>> &getE() const {
		return _bjfuMap.getE();
	}

	Structure::GraphMatrix<ScenicSpot, TourRoute> *get_bjfuMap();

    MapServiceReturnType createSpot(const Structure::String &spotName,
                                    const Structure::String &spotInfo);

    MapServiceReturnType editSpot(const Structure::String &spotName,
                                  const Structure::String &newInfo);

    MapServiceReturnType deleteSpot(const Structure::String &spotName);

    MapServiceReturnType createRoute(const Structure::String &firstPointName,
                                     const Structure::String &secondPointName,
                                     int distance);

    MapServiceReturnType deleteRoute(const Structure::String &firstPointName,
                                     const Structure::String &secondPointName);

    Structure::GraphMatrix<ScenicSpot, TourRoute> *OptimalRouteDesign();

protected:
    void dataBaseUpdate();

    Rank getVertexId(const Structure::String &name);

    MapServiceReturnType InsertUndirectedEdges(const Structure::String &firstPointName,
                                               const Structure::String &secondPointName,
                                               TourRoute distance);

    MapServiceReturnType RemoveUndirectedEdges(const Structure::String &firstPointName,
                                               const Structure::String &secondPointName);

    Structure::Stack<ScenicSpot> getShortestPath(Rank i, Rank j, int &shortestLength);

};

#endif //BJFU_TOUR_GUIDE_BACKGROUNDCONTROLLER_H
