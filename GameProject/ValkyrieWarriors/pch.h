#ifndef PCH_H
#define PCH_H

#include <fstream>
#include <sstream>
#include <iostream>
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
#include <SDL_ttf.h>

#include <Effekseer.h>
#include <EffekseerRendererGL.h>

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
#include "PlayerObjectStateDamage.h"
#include "PlayerObjectStateDeath.h"
#include "PlayerWeaponObject.h"

#include "EnemyObjectManager.h"
#include "EnemysControler.h"
#include "CreateEnemys.h"
#include "EnemyObject.h"
#include "EnemyAttackDecisionObject.h"
#include "EnemyGenerator.h"
#include "EnemyGeneratorBlackBoard.h"
#include "EnemyObjectStateBase.h"
#include "EnemyObjectStateTrack.h"
#include "EnemyObjectStateWait.h"
#include "EnemyObjectStateAttack.h"
#include "EnemyObjectStateAttackReady.h"
#include "EnemyObjectStateMove.h"
#include "EnemyObjectStateImpactDamage.h"
#include "EnemyObjectStateSweepFallDamage.h"
#include "EnemyObjectStateFlyingBackDamage.h"
#include "EnemyObjectStateStandUp.h"
#include "EnemyObjectStateFallingBackDeath.h"
#include "EnemyObjectStateSweepFallDeath.h"
#include "EnemyObjectStateFlyingBackDeath.h"

#include "BossObject.h"
#include "BossObjectStateBase.h"
#include "BossObjectStateWait.h"
#include "BossObjectStateTrack.h"
#include "BossObjectStateFrontAttack.h"
#include "BossObjectStateAreaAttack.h"
#include "BossObjectStateOverheadAttack.h"
#include "BossObjectStateTeleportation.h"
#include "BossObjectStateImpactDamage.h"
#include "BossObjectStateFlyingBackDamage.h"
#include "BossObjectStateSweepFallDamage.h"
#include "BossObjectStateDeath.h"

#include "DeadObjectEnable.h"
#include "DeadObjectActiveBox.h"
#include "SemitransparentWallEnabler.h"
#include "SemitransparentWall.h"

#include "GroundObject.h"

#include "OpenGate.h"
#include "GateObject.h"
#include "GateDoorObject.h"

#include "WallObject.h"

#include "CircleShadowObject.h"

#include "MainCameraObject.h"

#include "Sprite.h"

#include "UIRoot.h"
#include "TextureSizeChanger.h"
#include "SpriteGauge.h"
#include "SpriteFrame.h"
#include "ParticleGauge.h"
#include "ParticleFrame.h"
#include "OperationExplanationBehavior.h"
#include "OperationExplanation.h"

#include "InputSystem.h"

#include "Component.h"
#include "PhysicsWorld.h"
#include "ColliderComponent.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"

#include "Renderer.h"
#include "HDRRenderer.h"
#include "DepthMap.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
#include "MeshComponent.h"
#include "AttackMeshComponent.h"
#include "SkeletalMeshComponent.h"
#include "ParticleComponent.h"
#include "SpriteComponent.h"
#include "EffectComponent.h"
#include "SelfRotation.h"

#include "Font.h"
#include "DeadEnemyCountTextChange.h"
#include "ActiveObjectDisable.h"
#include "DeadEnemyCountText.h"
#include "DefeatEnemyNumberText.h"

#include "CubeMapComponent.h"
#include "SkyBoxObject.h"

#include "SceneBase.h"
#include "TitleScene.h"
#include "ActionScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

#include "FPS.h"
#include "Math.h"
#include "RapidJsonHelper.h"

#include "EffekseerEffect.h"

#include "FirstAttackEffect.h"
#include "SecondAttackEffect.h"
#include "ThirdAttackEffect.h"
#include "DashAttackEffect.h"
#include "HitEffect.h"
#include "FrontLaserMagicEffect.h"
#include "FrontCoreMagicEffect.h"
#include "AreaMagicEffect.h"
#include "OverheadMagicEffect.h"
#include "DangerSignalEffect.h"
#include "ChantEffect.h"
#include "TeleportationEffect.h"

#endif