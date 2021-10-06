#ifndef PCH_H
#define PCH_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
#include <map>
#include <functional>
#include <typeinfo>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <limits>
#include <unordered_map>

#include <stdio.h>
#include <limits.h>
#include <memory.h>
#include <document.h>
#include <filereadstream.h>
#include <glew.h>
#include <SDL.h>
#include <SDL_log.h>
#include <SDL_image.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include "Game.h"

#include "Animation.h"
#include "Skeleton.h"
#include "BoneTransform.h"
#include "MatrixPalette.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "MapCreate.h"
#include "PlayerObject.h"
#include "PlayerObjectStateBase.h"
#include "PlayerObjectStateIdle.h"
#include "PlayerObjectStateSprintStart.h"
#include "PlayerObjectStateRunLoop.h"
#include "PlayerObjectStateSprintLoop.h"
#include "PlayerObjectStateFirstAttack.h"
#include "PlayerObjectStateSecondAttack.h"
#include "PlayerObjectStateThirdAttack.h"
#include "PlayerObjectStateDashAttack.h"
#include "EnemyObject.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateTrack.h"
#include "EnemyObjectStateWait.h"
#include "EnemyObjectStateAttack.h"
#include "EnemyObjectStateMove.h"
#include "EnemyObjectStateDamage.h"
#include "EnemyObjectStateDeath.h"
#include "GroundObject.h"
#include "WallObject.h"
#include "MainCameraObject.h"
#include "Sprite.h"

#include "InputSystem.h"

#include "Component.h"
#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"

#include "Renderer.h"
#include "HDRRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "MeshComponent.h"
#include "AttackMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "ParticleComponent.h"
#include "SpriteComponent.h"
#include "UIComponent.h"

#include "SceneBase.h"
#include "TitleScene.h"
#include "Tutorial.h"

#include "FPS.h"
#include "Math.h"
#include "RapidJsonHelper.h"

#endif