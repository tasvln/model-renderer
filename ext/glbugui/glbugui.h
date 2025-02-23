#ifndef GL_DEBUG_INTERFACE_H
#define GL_DEBUG_INTERFACE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>

namespace glbugui
{
  class Element
  {
  public:
    virtual ~Element() = default;
    virtual void render(unsigned int fontTexture, stbtt_bakedchar *charData) = 0;
  };

  class Text : public Element
  {
  public:
    float x, y;
    std::string text;
    std::function<std::string()> dynamicText;
    bool isDynamic;
    glm::vec4 color;

    Text(float x, float y, const char *text, glm::vec4 color)
    {
      this->x = x;
      this->y = y;
      this->text = text;
      this->isDynamic = false;
      this->color = color;
    }

    Text(float x, float y, std::function<std::string()> textFunc, glm::vec4 color)
    {
      this->x = x;
      this->y = y;
      this->dynamicText = textFunc;
      this->isDynamic = true;
      this->color = color;
    }

    // Implement the render method
    void render(unsigned int fontTexture, stbtt_bakedchar *charData)
    {
      renderText(x, y, isDynamic ? dynamicText().c_str() : &text[0], fontTexture, charData);
    }

    void renderText(float x, float y, const char *text, unsigned int fontTexture, stbtt_bakedchar *charData)
    {

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, fontTexture);

      glColor4f(color.r, color.g, color.b, color.a);

      glBegin(GL_QUADS);

      while (*text)
      {
        if (static_cast<unsigned char>(*text) >= 32 && static_cast<unsigned char>(*text) < 128)
        {
          stbtt_aligned_quad q;
          stbtt_GetBakedQuad(charData, 512, 512, *text - 32, &x, &y, &q, 1);
          glTexCoord2f(q.s0, q.t0);
          glVertex2f(q.x0, q.y0);
          glTexCoord2f(q.s1, q.t0);
          glVertex2f(q.x1, q.y0);
          glTexCoord2f(q.s1, q.t1);
          glVertex2f(q.x1, q.y1);
          glTexCoord2f(q.s0, q.t1);
          glVertex2f(q.x0, q.y1);
        }
        ++text;
      }
      glEnd();
    }
  };

  class GlBugUi
  {
  public:
    // Constructors
    explicit GlBugUi(GLFWwindow *window, std::string filePath)
    {
      if (!loadFont(filePath.c_str()))
      { // Load the font when initializing GlBugUi
        std::cerr << "Failed to load font.\n";
      }

      this->window = window;
    }

    ~GlBugUi()
    {
      for (Element *element : elements)
      {
        delete element;
      }
      elements.clear();
    }

    // A templated function to create and add elements
    template <typename T, typename... Args>
    T *addElement(Args &&...args)
    {
      cout << "addElement: adding element" << endl;
      T *element = new T(std::forward<Args>(args)...);
      elements.push_back(element);
      return element;
    }

    void render()
    {
      for (Element *element : elements)
      {
        element->render(fontTexture, charData);
      }
    }

  private:
    GLFWwindow *window;
    std::vector<Element *> elements;

    stbtt_fontinfo font;
    unsigned int fontTexture;
    unsigned char ttf_buffer[1 << 20];
    unsigned char fontBitmap[512 * 512];
    stbtt_bakedchar charData[96]; // ASCII 32-126

    int fontSize = 50;

    bool loadFont(const char *filename)
    {
      FILE *file = fopen(filename, "rb");
      if (file == nullptr)
      {
        std::cerr << "Error: Failed to open font file: " << filename << std::endl;
      }
      else
      {
        // Proceed to read the file
        fread(ttf_buffer, 1, 1 << 20, file);
        fclose(file);
      }

      stbtt_BakeFontBitmap(ttf_buffer, 0, fontSize, fontBitmap, 512, 512, 32, 96, charData);

      glGenTextures(1, &fontTexture);
      glBindTexture(GL_TEXTURE_2D, fontTexture);

      if (fontTexture)
      {
        cout << "fontTexture Loaded" << endl;
      }
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, fontBitmap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      cout << "font loaded end" << endl;

      return true;
    }
  };
}

#endif
