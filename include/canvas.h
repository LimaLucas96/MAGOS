#ifndef CANVAS_H
#define CANVAS_H

#include <stdexcept>
#include <iostream>

#include <memory>  // unique_ptr<>
#include <cstring> // memset, memcpy

#include "common.h"

namespace canvas {

    //! Provides methods for drawing on an image.
    /*!
     * This is a drawing area on which we shall draw a maze representation.
     *
     * Here some information on the canvas properties:
     *
     * 1. The drawing area has the origin set to the top left corner, with
     * positive `X` axis going to the right and positive `Y` axis going to
     * the bottom of the canvas.
     * 2. Canvas supports basic operations to draw on vertical and horizontal
     * lines, as well as filled bordeless boxes.
     * 3. It is also possible to change line thikness to improve the final
     * appearance of the maze repreentation on the output image.
     *
     * This class returns to the client a pointer to the bytes (image) that
     * represents the pixels, which might be recorded by the client as an PPM
     * or PNG image file.
     */
    class Canvas
    {
        public:
            //=== Alias
            typedef unsigned char component_t; //!< Type of a color channel.

        public:

            //=== Special members
            /// Constructor
            /*! Creates an empty canvas of the requested size.
             * @param w_ The canvas width (in pixels).
             * @param h_ The canvas height (in pixels).
             */
            Canvas( size_t w=0, size_t h=0 )
                : m_width{w}, m_height{h},
                  m_pixels{  new component_t [ m_height * m_width * 3 ] },
                  m_line_thikness{1}
            { std::memset( m_pixels, 255, ( m_height * m_width * 3 )); }

            /// Destructor.
            virtual ~Canvas( void )
            {
                // TODO
            }

            //=== Special members
            /// Copy constructor.uo
            Canvas( const Canvas & );
            /// Assignment operator.
            Canvas & operator=( const Canvas & );

            //=== Members
            /// Clear the canvas with the background color.
            void clear( const Color& );
            /// Reset canvas.
            void reset(size_t w, size_t h); // <======================== Implementar
            /// Change the current line thickness.
            void thickness( unsigned short lt )
            { m_line_thikness = lt; }
            /// Get the current line thickness.
            unsigned short thickness( void ) const
            { return m_line_thikness; }
            /// Set the color of a pixel on the canvas.
            void pixel( coord_type x, coord_type y,  const Color& );
            /// Get the pixel color from the canvas.
            Color pixel( coord_type x, coord_type y ) const;

            //=== Attribute accessors members.
            /// Get the canvas width.
            size_t width( void ) const
            { return m_width; }
            /// Get the cancas height.
            size_t height( void ) const
            { return m_height; }
            /// Get the canvas pixels, as an array of `unsigned char`.
            component_t* buffer( void ) const
            { return m_pixels; }

            /// Draw a horizontal line with `length` pixels on the canvas, starting at a `p` location.
            /*
             * Example:
             *
             * ```
             * (p.x, p.y), thickness = 3, length = 15.
             *  |
             *  v
             *  . . . . . . . . . . . . . . .
             *  . . . . . . . . . . . . . . .
             *  . . . . . . . . . . . . . . .
             *  ```
             */
            void hline( coord_type x, coord_type y, size_t length, const Color& c );
            /// Draw a vertical line with `length` pixels on the canvas, starting at a `p` location.
            /*
             * Example:
             *
             * ```
             * (p.x, p.y), thickness = 3, length = 6.
             *  |
             *  v
             *  . . .
             *  . . .
             *  . . .
             *  . . .
             *  . . .
             *  . . .
             *  ```
             */
            void vline( coord_type x, coord_type y,  size_t length, const Color& c );
            /// Draw a filled box, with origin at `p` (the top-left corner).
            void box( coord_type x, coord_type y, size_t width, size_t height, const Color& c );

        private:
            size_t m_width; //!< The image width in pixel units.
            size_t m_height; //!< The image height in pixel unitsr
            component_t *m_pixels; //!< The pixels, stored as 3 RGB components.
            unsigned short m_line_thikness; //!< Current line thickness.
    };

       /*!
     * Deep copy of the canvas.
     * @param clone The object we are copying from.
     */
    Canvas::Canvas( const Canvas & clone )
    {
        m_width = clone.m_width;
        m_height = clone.m_height;

        m_pixels = new component_t[m_width * m_height * 3];
        m_line_thikness = clone.m_line_thikness;

        for(auto i(0); i < m_width * m_height * 3; i++){
            m_pixels[i] = clone.m_pixels[i];
        }
    }


    /*!
     * @param source The object we are copying information from.
     * @return A reference to the `this` object.
     */
    Canvas& Canvas::operator=( const Canvas & source )
    {
        // TODO: incompleto
        m_width = source.m_width;
        m_height = source.m_height;

        m_pixels = new component_t[m_width * m_height * 3];
        m_line_thikness = source.m_line_thikness;

        for(auto i(0); i < m_width * m_height * 3; i++){
            m_pixels[i] = source.m_pixels[i];
        }

        return *this;
    }

    void Canvas::clear( const Color& color )
    {
        // TODO
        for(auto i(0); i < m_width * m_height * 3; i+=3){
            m_pixels[i + 0] = color.channels[0];
            m_pixels[i + 1] = color.channels[1];
            m_pixels[i + 2] = color.channels[2]; 
        }

    }

    void Canvas::reset(size_t w, size_t h){
        m_width = w;
        m_height = h;

        m_pixels = new component_t[ m_width * m_height * 3];

        std::memset( m_pixels, 255, ( m_height * m_width * 3 ));
    }

    /*!
     * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
     * @param p The 2D coordinate of the pixel we want to know the color of.
     * @return The pixel color.
     */
    Color Canvas::pixel( coord_type x, coord_type y ) const
    {
        // TODO
        if(y > m_width or x > m_height){
            throw std::invalid_argument("the pixel coordinate is located outside the canvas.");
        }

        auto coordinate = y * m_width * 3 + x * 3;
        auto R = m_pixels [coordinate + 0];
        auto G = m_pixels [coordinate + 1];
        auto B = m_pixels [coordinate + 2];

        return Color(R,G,B); 
    }

    /*!
     * @note Nothing is done if the  pixel coordinate is located outside the canvas.
     * @param p The 2D coordinate of the pixel we want to change the color.
     * @param c The color.
     */
    void Canvas::pixel( coord_type x, coord_type y, const Color& c )
    {
        // TODO
        if(m_width >= y and m_height >= x){
            auto coordinate = y * m_width * 3 + x * 3;
            m_pixels [coordinate + 0] = c.channels[0];
            m_pixels [coordinate + 1] = c.channels[1];
            m_pixels [coordinate + 2] = c.channels[2];
        }
    }


    /*!
     * Draws on the canvas a horizontal line.
     * @param p The 2D coordinate of the initial pixel of the line.
     * @param length The horizontal length of the line in pixels.
     */
    void Canvas::hline( coord_type x, coord_type y, size_t length, const Color& color )
    {
        // TODO
        auto posX = x;
        int aux(0);

        while (aux <= m_line_thikness){
            x = posX;
            for(auto comp(0); comp <= length + m_line_thikness; comp++){

                auto coordinate = y * m_width * 3 + x * 3;
                m_pixels [coordinate + 0] = color.channels[0];
                m_pixels [coordinate + 1] = color.channels[1];
                m_pixels [coordinate + 2] = color.channels[2];
                x++;
            }
            y++;
            aux++;
        }
    }

    /*!
     * Draws on the canvas a vertical line.
     * @param p The 2D coordinate of the initial pixel of the line.
     * @param length The vertical length of the line in pixels.
     */
    void Canvas::vline( coord_type x, coord_type y, size_t length, const Color& color )
    {
        // TODO
        auto posY = y;
        int aux(0);

        while (aux <= m_line_thikness){
            y = posY; 
            for(auto comp(0); comp <= length + m_line_thikness; comp++){

                auto coordinate = y * m_width * 3 + x * 3;
                m_pixels [coordinate + 0] = color.channels[0];
                m_pixels [coordinate + 1] = color.channels[1];
                m_pixels [coordinate + 2] = color.channels[2];
                y++;
            }
            x++;
            aux++;
        }
    }

    /*!
     * Draws on the canvas a filled box. The origin of the box is the top-left corner.
     * The box is compose of horizontal lines, drawn top to bottom.
     * @param p The 2D coordinate of the initial pixel of the box (top-left corner).
     * @param width The box's width in pixels.
     * @param height The box's heigth in pixels.
     */
    void Canvas::box( coord_type x, coord_type y, size_t width, size_t height , const Color& color)
    {
        // TODO
        auto posX = x;
        for(auto w(0); w < width ; w++){
            x = posX;

            for(auto h(0); h < height; h++){
                auto coordinate = y * m_width * 3 + x * 3;
                m_pixels [coordinate + 0] = color.channels[0];
                m_pixels [coordinate + 1] = color.channels[1];
                m_pixels [coordinate + 2] = color.channels[2];

                x++;
            }
            y++;
        }
    }
} // namespace

#endif // CANVAS_H
