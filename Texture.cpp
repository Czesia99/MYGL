#include "Texture.hpp"

#include <iostream>
#include <glad/glad.h>
#include "stb_image.h"

namespace mygl
{
    void loadTexture(const char *file, unsigned int &texture, int min_filter, int mag_filter, int wrap)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &texture);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(file, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            GLenum storage_format;

            if (nrComponents == 1) {
                format = GL_RED;
                storage_format = GL_R8;
            }
            else if (nrComponents == 3) {
                format = GL_RGB;
                storage_format = GL_RGB8;
            }
            else if (nrComponents == 4) {
                format = GL_RGBA;
                storage_format = GL_RGBA8;
            }

            // glBindTexture(GL_TEXTURE_2D, texture);
            // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrap); //second argument was GL_REPEAT
            glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrap); //second argument was GL_REPEAT
            glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min_filter);
            glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag_filter);

            glTextureStorage2D(texture, 1, storage_format, width, height);
            glTextureSubImage2D(texture, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
            glGenerateTextureMipmap(texture);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << file << std::endl;
            stbi_image_free(data);
        }
    }

    void loadTextureArray(std::vector<std::string>files, unsigned int &texture, int width, int height, int min_filter, int mag_filter, int wrap)
    {
        stbi_set_flip_vertically_on_load(true);
        glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &texture);
        int nrComponents;

        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, wrap);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, wrap);
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, min_filter);
        glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, mag_filter);
        glTextureStorage3D(texture, 4, GL_RGBA8, width, height, files.size());

        for (int i = 0; i < files.size(); i++)
        {
            unsigned char *data = stbi_load(files[i].c_str(), &width, &height, &nrComponents, 0);
            if (data) {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glTextureSubImage3D(texture, 0, 0, 0, i, width, height, 1, format, GL_UNSIGNED_BYTE, data);
                glGenerateTextureMipmap(texture);
                stbi_image_free(data);
            } else
            {
                std::cout << "Texture failed to load at path: " << files[i] << std::endl;
            }
        }
    }
}