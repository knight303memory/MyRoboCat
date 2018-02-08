//
// Created by Killua on 2018/2/4.
//

#ifndef MYROBOCAT_MYROBOCATPCH_H
#define MYROBOCAT_MYROBOCATPCH_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;

#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <list>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cassert>
#include <map>
#include <random>


using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;
using std::map;

class MyRoboCat;

class GameObject;

#include "Engine.h"
#include "RandGen.h"
#include "RoboMath.h"
#include "SocketUtil.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "GameObject.h"
#include "GameObjectRegistry.h"
#include "World.h"
#include "ScoreBoardManager.h"
#include "WindowManager.h"

#include <SDL.h>
#endif //MYROBOCAT_MYROBOCATPCH_H
