#include "pch.h"
#include "MapService.h"
#include <fstream>

MapService::MapService()
{
	std::ifstream inFile;
	inFile.open(UWPHelper::getFilePath("map.txt"), std::ios::in | std::ios::binary);
	if (inFile.fail())
	{
		CurrentStatus = MapServiceStatus::DB_ERROR;
	}
	int vNum, eNum;
	inFile >> vNum >> eNum;
	for (int i = 0; i < vNum; i++)
	{
		ScenicSpot newSpot;
		inFile >> newSpot;
		_bjfuMap.insert(newSpot);
	}
	for (int i = 0; i < eNum; i++)
	{
		Structure::String firstPointName, secondPointName;
		TourRoute distance;
		inFile >> firstPointName >> secondPointName >> distance;
		InsertUndirectedEdges(firstPointName, secondPointName, distance);
	}
	CurrentStatus = MapServiceStatus::DB_SUCCESS;
	inFile.close();
}

MapService::~MapService()
{
	dataBaseUpdate();
}

MapServiceStatus MapService::getCurrentStatus() const
{
	return CurrentStatus;
}

Structure::Vector<ScenicSpot> MapService::getSpotInfoByName(const Structure::String &spotName)
{
	Structure::Vector<ScenicSpot> result;
	Rank index = getVertexId(spotName);
	if (index != -1)
	{
		result.insert(_bjfuMap.vertex(index));
	}
	return result;
}

Structure::Vector<ScenicSpot> MapService::getSpotListByFunction(const Structure::String &function)
{
	Structure::Vector<ScenicSpot> result;
	if (function.length() == 0)
	{
		return result;
	}
	SpotFunction spotFunctionToSearch = SpotFunction::AMBIGUOUS;
	// 匹配预设功能
	if (function.find("课") != function.length())
	{
		spotFunctionToSearch = SpotFunction::TEACHING;
	}
	else if (function.find("自习") != function.length())
	{
		spotFunctionToSearch = SpotFunction::SELF_STUDY;
	}
	else if (function.find("宿舍") != function.length() ||
			 function.find("住") != function.length())
	{
		spotFunctionToSearch = SpotFunction::ACCOMMODATION;
	}
	else if (function.find("办公") != function.length())
	{
		spotFunctionToSearch = SpotFunction::OFFICE;
	}
	else if (function.find("饭") != function.length() ||
			 function.find("食") != function.length())
	{
		spotFunctionToSearch = SpotFunction::RESTAURANT;
	}
	if (spotFunctionToSearch != SpotFunction::AMBIGUOUS)
	{
		// 遍历节点数组并在其中寻找预设功能
		for (int i = 0; i < _bjfuMap.vNum; i++)
		{
			if (_bjfuMap.vertex(i).get_function().find(spotFunctionToSearch) != -1)
			{
				result.insert(_bjfuMap.vertex(i));
			}
		}
	}
	else
	{
		// 遍历节点数组逐个KMP搜索
		for (int i = 0; i < _bjfuMap.vNum; i++)
		{
			auto currentStr = _bjfuMap.vertex(i).get_info();
			if (currentStr.find(function) != currentStr.length())
			{
				result.insert(_bjfuMap.vertex(i));
			}
		}
	}
	return result;
}

Structure::Stack<ScenicSpot>
MapService::getShortestPath(const Structure::String &firstPointName,
							const Structure::String &secondPointName,
							int &shortestLength)
{
	Rank firstPoint = getVertexId(firstPointName);
	Rank secondPoint = getVertexId(secondPointName);
	if (firstPoint == -1 || secondPoint == -1)
	{
		shortestLength = INT_MAX;
		return Structure::Stack<ScenicSpot>();
	}
	return getShortestPath(firstPoint, secondPoint, shortestLength);
	;
}

Structure::Vector<Structure::Stack<ScenicSpot>>
MapService::getAllPath(const Structure::String &firstPointName, const Structure::String &secondPointName)
{
	Rank firstPoint = getVertexId(firstPointName);
	Rank secondPoint = getVertexId(secondPointName);
	if (firstPoint == -1 || secondPoint == -1)
	{
		return Structure::Vector<Structure::Stack<ScenicSpot>>();
	}
	return _bjfuMap.dfsFindAllPath(firstPoint, secondPoint);
}

MapServiceReturnType
MapService::createSpot(const Structure::String &spotName, const Structure::String &spotInfo)
{
	if (getVertexId(spotName) == -1)
	{
		_bjfuMap.insert(ScenicSpot(spotName, spotInfo));
		dataBaseUpdate();
		return MapServiceReturnType::SUCCESS;
	}
	else
	{
		return MapServiceReturnType::SPOT_HAS_EXISTED;
	}
}

MapServiceReturnType
MapService::editSpot(const Structure::String &spotName, const Structure::String &newInfo)
{
	Rank index = getVertexId(spotName);
	if (index != -1)
	{
		_bjfuMap.vertex(index).set_info(newInfo);
		dataBaseUpdate();
		return MapServiceReturnType::SUCCESS;
	}
	else
	{
		return MapServiceReturnType::SPOT_NOT_EXIST;
	}
}

MapServiceReturnType MapService::deleteSpot(const Structure::String &spotName)
{
	Rank index = getVertexId(spotName);
	if (index != -1)
	{
		_bjfuMap.remove(index);
		dataBaseUpdate();
		return MapServiceReturnType::SUCCESS;
	}
	else
	{
		return MapServiceReturnType::SPOT_NOT_EXIST;
	}
}

MapServiceReturnType
MapService::createRoute(const Structure::String &firstPointName, const Structure::String &secondPointName,
						int distance)
{
	auto status = InsertUndirectedEdges(firstPointName, secondPointName, TourRoute(distance));
	dataBaseUpdate();
	return status;
}

MapServiceReturnType
MapService::deleteRoute(const Structure::String &firstPointName, const Structure::String &secondPointName)
{
	auto status = RemoveUndirectedEdges(firstPointName, secondPointName);
	dataBaseUpdate();
	return status;
}

void MapService::dataBaseUpdate()
{
	std::ofstream outFile;
	outFile.open(UWPHelper::getFilePath("map.txt"), std::ios::out | std::ios::binary);
	if (!outFile)
	{
		CurrentStatus = MapServiceStatus::DB_ERROR;
	}
	// 无向图 两条边相当于一条
	outFile << _bjfuMap.vNum << " " << _bjfuMap.eNum / 2 << std::endl;
	for (int i = 0; i < _bjfuMap.vNum; i++)
	{
		outFile << _bjfuMap.vertex(i) << std::endl;
	}
	for (int i = 0; i < _bjfuMap.vNum; i++)
	{
		for (int j = i + 1; j < _bjfuMap.vNum; j++)
		{
			if (_bjfuMap.exists(i, j))
			{
				outFile << _bjfuMap.vertex(i).get_name() << " "
						<< _bjfuMap.vertex(j).get_name() << " "
						<< _bjfuMap.edge(i, j) << std::endl;
			}
		}
	}
	CurrentStatus = MapServiceStatus::DB_SUCCESS;
	outFile.close();
}

Rank MapService::getVertexId(const Structure::String &name)
{
	for (int i = 0; i < _bjfuMap.vNum; i++)
	{
		if (_bjfuMap.vertex(i).get_name() == name)
		{
			return i;
		}
	}
	return -1;
}

MapServiceReturnType MapService::InsertUndirectedEdges(const Structure::String &firstPointName,
													   const Structure::String &secondPointName,
													   TourRoute distance)
{
	Rank firstPoint = getVertexId(firstPointName);
	Rank secondPoint = getVertexId(secondPointName);
	if (firstPoint == -1 || secondPoint == -1)
	{
		return MapServiceReturnType::SPOT_NOT_EXIST;
	}
	if (_bjfuMap.exists(firstPoint, secondPoint) ||
		_bjfuMap.exists(secondPoint, firstPoint))
	{
		return MapServiceReturnType::ROUTE_HAS_EXIST;
	}
	else
	{
		_bjfuMap.insert(distance, distance.get_routeLength(),
						firstPoint, secondPoint);
		_bjfuMap.insert(distance, distance.get_routeLength(),
						secondPoint, firstPoint);
		return MapServiceReturnType::SUCCESS;
	}
}

MapServiceReturnType
MapService::RemoveUndirectedEdges(const Structure::String &firstPointName,
								  const Structure::String &secondPointName)
{
	Rank firstPoint = getVertexId(firstPointName);
	Rank secondPoint = getVertexId(secondPointName);
	if (firstPoint == -1 || secondPoint == -1)
	{
		return MapServiceReturnType::SPOT_NOT_EXIST;
	}
	if (!_bjfuMap.exists(firstPoint, secondPoint) ||
		!_bjfuMap.exists(secondPoint, firstPoint))
	{
		return MapServiceReturnType::ROUTE_NOT_EXIST;
	}
	else
	{
		_bjfuMap.remove(firstPoint, secondPoint);
		_bjfuMap.remove(secondPoint, firstPoint);
		return MapServiceReturnType::SUCCESS;
	}
}

Structure::Stack<ScenicSpot> MapService::getShortestPath(Rank i, Rank j, int &shortestLength)
{
	Structure::Stack<ScenicSpot> path;
	_bjfuMap.dijkstra(i);
	shortestLength = _bjfuMap.priority(j);
	while (i != j)
	{
		path.push(_bjfuMap.vertex(j));
		j = _bjfuMap.parent(j);
	}
	path.push(_bjfuMap.vertex(i));
	return path;
}

Structure::GraphMatrix<ScenicSpot, TourRoute> *MapService::OptimalRouteDesign()
{
	_bjfuMap.prim(0);
	return &_bjfuMap;
}

Structure::GraphMatrix<ScenicSpot, TourRoute> *MapService::get_bjfuMap()
{
	return &_bjfuMap;
}
