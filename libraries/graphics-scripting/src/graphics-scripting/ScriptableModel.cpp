//
//  ScriptableModel.cpp
//  libraries/graphics-scripting
//
//  Copyright 2018 High Fidelity, Inc.
//  Copyright 2023 Overte e.V.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//  SPDX-License-Identifier: Apache-2.0
//

#include "ScriptableModel.h"

#include <ScriptValue.h>

#include "GraphicsScriptingUtil.h"
#include "ScriptableMesh.h"
#include "graphics/Material.h"
#include "image/TextureProcessing.h"

// #define SCRIPTABLE_MESH_DEBUG 1

scriptable::ScriptableMaterial& scriptable::ScriptableMaterial::operator=(const scriptable::ScriptableMaterial& material) {
    name = material.name;
    model = material.model;
    opacity = material.opacity;
    albedo = material.albedo;

    if (model.toStdString() == graphics::Material::HIFI_PBR || model.toStdString() == graphics::Material::VRM_MTOON) {
        opacityCutoff = material.opacityCutoff;
        opacityMapMode = material.opacityMapMode;
        emissive = material.emissive;
        emissiveMap = material.emissiveMap;
        albedoMap = material.albedoMap;
        opacityMap = material.opacityMap;
        normalMap = material.normalMap;
        bumpMap = material.bumpMap;
        cullFaceMode = material.cullFaceMode;

        layers = material.layers;
        splatMap = material.splatMap;

        if (model.toStdString() == graphics::Material::HIFI_PBR) {
            roughness = material.roughness;
            metallic = material.metallic;
            scattering = material.scattering;
            unlit = material.unlit;
            metallicMap = material.metallicMap;
            specularMap = material.specularMap;
            roughnessMap = material.roughnessMap;
            glossMap = material.glossMap;
            occlusionMap = material.occlusionMap;
            lightMap = material.lightMap;
            scatteringMap = material.scatteringMap;
        } else {
            shade = material.shade;
            shadeMap = material.shadeMap;
            shadingShift = material.shadingShift;
            shadingShiftMap = material.shadingShiftMap;
            shadingToony = material.shadingToony;
            matcap = material.matcap;
            matcapMap = material.matcapMap;
            parametricRim = material.parametricRim;
            parametricRimFresnelPower = material.parametricRimFresnelPower;
            parametricRimLift = material.parametricRimLift;
            rimMap = material.rimMap;
            rimLightingMix = material.rimLightingMix;
            outlineWidthMode = material.outlineWidthMode;
            outlineWidth = material.outlineWidth;
            outline = material.outline;
            uvAnimationMaskMap = material.uvAnimationMaskMap;
            uvAnimationScrollXSpeed = material.uvAnimationScrollXSpeed;
            uvAnimationScrollYSpeed = material.uvAnimationScrollYSpeed;
            uvAnimationRotationSpeed = material.uvAnimationRotationSpeed;
        }
    } else if (model.toStdString() == graphics::Material::HIFI_SHADER_SIMPLE) {
        procedural = material.procedural;
    }

    defaultFallthrough = material.defaultFallthrough;
    propertyFallthroughs = material.propertyFallthroughs;

    key = material.key;

    return *this;
}

scriptable::ScriptableMaterial::ScriptableMaterial(const graphics::MaterialPointer& material) {
    if (material) {
        name = material->getName().c_str();
        model = material->getModel().c_str();
        opacity = material->getOpacity();
        albedo = material->getAlbedo();

        if (model.toStdString() == graphics::Material::HIFI_PBR || model.toStdString() == graphics::Material::VRM_MTOON) {
            opacityCutoff = material->getOpacityCutoff();
            opacityMapMode = QString(graphics::MaterialKey::getOpacityMapModeName(material->getOpacityMapMode()).c_str());
            emissive = material->getEmissive();

            auto map = material->getTextureMap(graphics::Material::MapChannel::EMISSIVE_MAP);
            if (map && map->getTextureSource()) {
                emissiveMap = map->getTextureSource()->getUrl().toString();
            }

            map = material->getTextureMap(graphics::Material::MapChannel::ALBEDO_MAP);
            if (map && map->getTextureSource()) {
                albedoMap = map->getTextureSource()->getUrl().toString();
                if (map->useAlphaChannel()) {
                    opacityMap = albedoMap;
                }
            }

            map = material->getTextureMap(graphics::Material::MapChannel::NORMAL_MAP);
            if (map && map->getTextureSource()) {
                if (map->getTextureSource()->getType() == image::TextureUsage::Type::NORMAL_TEXTURE) {
                    normalMap = map->getTextureSource()->getUrl().toString();
                } else if (map->getTextureSource()->getType() == image::TextureUsage::Type::BUMP_TEXTURE) {
                    bumpMap = map->getTextureSource()->getUrl().toString();
                }
            }

            for (int i = 0; i < graphics::Material::NUM_TEXCOORD_TRANSFORMS; i++) {
                texCoordTransforms[i] = material->getTexCoordTransform(i);
            }

            cullFaceMode = QString(graphics::MaterialKey::getCullFaceModeName(material->getCullFaceMode()).c_str());

            layers = material->getLayers();
            map = material->getTextureMap(graphics::Material::MapChannel::SPLAT_MAP);
            if (map && map->getTextureSource()) {
                splatMap = map->getTextureSource()->getUrl().toString();
            }

            if (model.toStdString() == graphics::Material::HIFI_PBR) {
                roughness = material->getRoughness();
                metallic = material->getMetallic();
                scattering = material->getScattering();
                unlit = material->isUnlit();

                map = material->getTextureMap(graphics::Material::MapChannel::METALLIC_MAP);
                if (map && map->getTextureSource()) {
                    if (map->getTextureSource()->getType() == image::TextureUsage::Type::METALLIC_TEXTURE) {
                        metallicMap = map->getTextureSource()->getUrl().toString();
                    } else if (map->getTextureSource()->getType() == image::TextureUsage::Type::SPECULAR_TEXTURE) {
                        specularMap = map->getTextureSource()->getUrl().toString();
                    }
                }

                map = material->getTextureMap(graphics::Material::MapChannel::ROUGHNESS_MAP);
                if (map && map->getTextureSource()) {
                    if (map->getTextureSource()->getType() == image::TextureUsage::Type::ROUGHNESS_TEXTURE) {
                        roughnessMap = map->getTextureSource()->getUrl().toString();
                    } else if (map->getTextureSource()->getType() == image::TextureUsage::Type::GLOSS_TEXTURE) {
                        glossMap = map->getTextureSource()->getUrl().toString();
                    }
                }

                map = material->getTextureMap(graphics::Material::MapChannel::OCCLUSION_MAP);
                if (map && map->getTextureSource()) {
                    occlusionMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::LIGHT_MAP);
                if (map && map->getTextureSource()) {
                    lightMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::SCATTERING_MAP);
                if (map && map->getTextureSource()) {
                    scatteringMap = map->getTextureSource()->getUrl().toString();
                }
            } else {
                shade = material->getShade();
                shadingShift = material->getShadingShift();
                shadingToony = material->getShadingToony();
                matcap = material->getMatcap();
                parametricRim = material->getParametricRim();
                parametricRimFresnelPower = material->getParametricRimFresnelPower();
                parametricRimLift = material->getParametricRimLift();
                rimLightingMix = material->getRimLightingMix();
                outlineWidthMode = material->getOutlineWidthMode();
                outlineWidth = material->getOutlineWidth();
                outline = material->getOutline();
                uvAnimationScrollXSpeed = material->getUVAnimationScrollXSpeed();
                uvAnimationScrollYSpeed = material->getUVAnimationScrollYSpeed();
                uvAnimationRotationSpeed = material->getUVAnimationRotationSpeed();

                // See the mappings in ProceduralMatericalCache.h
                map = material->getTextureMap(graphics::Material::MapChannel::ROUGHNESS_MAP);
                if (map && map->getTextureSource()) {
                    shadeMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::METALLIC_MAP);
                if (map && map->getTextureSource()) {
                    shadingShiftMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::OCCLUSION_MAP);
                if (map && map->getTextureSource()) {
                    matcapMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::SCATTERING_MAP);
                if (map && map->getTextureSource()) {
                    rimMap = map->getTextureSource()->getUrl().toString();
                }

                map = material->getTextureMap(graphics::Material::MapChannel::LIGHT_MAP);
                if (map && map->getTextureSource()) {
                    uvAnimationMaskMap = map->getTextureSource()->getUrl().toString();
                }
            }
        } else if (model.toStdString() == graphics::Material::HIFI_SHADER_SIMPLE) {
            procedural = material->getProceduralString();
        }

        defaultFallthrough = material->getDefaultFallthrough();
        propertyFallthroughs = material->getPropertyFallthroughs();

        key = material->getKey();
    }
}

scriptable::ScriptableMaterialLayer& scriptable::ScriptableMaterialLayer::operator=(const scriptable::ScriptableMaterialLayer& materialLayer) {
    material = materialLayer.material;
    priority = materialLayer.priority;

    return *this;
}

scriptable::ScriptableModelBase& scriptable::ScriptableModelBase::operator=(const scriptable::ScriptableModelBase& other) {
    provider = other.provider;
    objectID = other.objectID;
    for (const auto& mesh : other.meshes) {
        append(mesh);
    }
    materialLayers = other.materialLayers;
    materialNames = other.materialNames;
    return *this;
}

scriptable::ScriptableModelBase::~ScriptableModelBase() {
#ifdef SCRIPTABLE_MESH_DEBUG
    qCDebug(graphics_scripting) << "~ScriptableModelBase" << this;
#endif
    // makes cleanup order more deterministic to help with debugging
    for (auto& m : meshes) {
        m.strongMesh.reset();
    }
    meshes.clear();
    materialLayers.clear();
    materialNames.clear();
}

void scriptable::ScriptableModelBase::append(scriptable::WeakMeshPointer mesh) {
    meshes << ScriptableMeshBase{ provider, this, mesh, this /*parent*/ };
}

void scriptable::ScriptableModelBase::append(const ScriptableMeshBase& mesh) {
    if (mesh.provider.lock().get() != provider.lock().get()) {
        qCDebug(graphics_scripting) << "warning: appending mesh from different provider..." << mesh.provider.lock().get() << " != " << provider.lock().get();
    }
    meshes << mesh;
}

void scriptable::ScriptableModelBase::appendMaterial(const graphics::MaterialLayer& materialLayer, int shapeID, std::string materialName) {
    ScriptableMaterialLayer layer = ScriptableMaterialLayer(materialLayer);
    materialLayers[QString::number(shapeID)].push_back(layer);
    materialLayers["mat::" + QString::fromStdString(materialName)].push_back(layer);
}

void scriptable::ScriptableModelBase::appendMaterials(const std::unordered_map<std::string, graphics::MultiMaterial>& materialsToAppend) {
    auto materialsToAppendCopy = materialsToAppend;
    for (auto& multiMaterial : materialsToAppendCopy) {
        while (!multiMaterial.second.empty()) {
            materialLayers[QString(multiMaterial.first.c_str())].push_back(ScriptableMaterialLayer(multiMaterial.second.top()));
            multiMaterial.second.pop();
        }
    }
}

void scriptable::ScriptableModelBase::appendMaterialNames(const std::vector<std::string>& names) {
    for (auto& name : names) {
        materialNames.append(QString::fromStdString(name));
    }
}

QString scriptable::ScriptableModel::toString() const {
    return QString("[ScriptableModel%1%2 numMeshes=%3]")
        .arg(objectID.isNull() ? "" : " objectID="+objectID.toString())
        .arg(objectName().isEmpty() ? "" : " name=" +objectName())
        .arg(meshes.size());
}

scriptable::ScriptableModelPointer scriptable::ScriptableModel::cloneModel(const QVariantMap& options) {
    scriptable::ScriptableModelPointer clone = scriptable::ScriptableModelPointer(new scriptable::ScriptableModel(*this));
    clone->meshes.clear();
    for (const auto &mesh : getConstMeshes()) {
        auto cloned = mesh->cloneMesh();
        if (auto tmp = qobject_cast<scriptable::ScriptableMeshBase*>(cloned)) {
            clone->meshes << *tmp;
            tmp->deleteLater(); // schedule our copy for cleanup
        } else {
            qCDebug(graphics_scripting) << "error cloning mesh" << cloned;
        }
    }
    return clone;
}


const scriptable::ScriptableMeshes scriptable::ScriptableModel::getConstMeshes() const {
    scriptable::ScriptableMeshes out;
    for (const auto& mesh : meshes) {
        const scriptable::ScriptableMesh* m = qobject_cast<const scriptable::ScriptableMesh*>(&mesh);
        if (!m) {
            m = scriptable::make_scriptowned<scriptable::ScriptableMesh>(mesh);
        } else {
            qCDebug(graphics_scripting) << "reusing scriptable mesh" << m;
        }
        const scriptable::ScriptableMeshPointer mp = scriptable::ScriptableMeshPointer(const_cast<scriptable::ScriptableMesh*>(m));
        out << mp;
    }
    return out;
}

scriptable::ScriptableMeshes scriptable::ScriptableModel::getMeshes() {
    scriptable::ScriptableMeshes out;
    for (auto& mesh : meshes) {
        scriptable::ScriptableMesh* m = qobject_cast<scriptable::ScriptableMesh*>(&mesh);
        if (!m) {
            m = scriptable::make_scriptowned<scriptable::ScriptableMesh>(mesh);
        } else {
            qCDebug(graphics_scripting) << "reusing scriptable mesh" << m;
        }
        scriptable::ScriptableMeshPointer mp = scriptable::ScriptableMeshPointer(m);
        out << mp;
    }
    return out;
}

#if 0
glm::uint32 scriptable::ScriptableModel::forEachVertexAttribute(const ScriptValue& callback) {
    glm::uint32 result = 0;
    scriptable::ScriptableMeshes in = getMeshes();
    if (in.size()) {
        foreach (scriptable::ScriptableMeshPointer meshProxy, in) {
            result += meshProxy->mapAttributeValues(callback);
        }
    }
    return result;
}
#endif
