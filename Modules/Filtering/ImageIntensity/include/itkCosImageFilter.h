/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkCosImageFilter_h
#define __itkCosImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "vnl/vnl_math.h"

namespace itk
{
namespace Functor
{
/**
 * \class Cos
 * \brief
 * \ingroup ITKImageIntensity
 */
template< class TInput, class TOutput >
class Cos
{
public:
  Cos() {}
  ~Cos() {}
  bool operator!=(const Cos &) const
  {
    return false;
  }

  bool operator==(const Cos & other) const
  {
    return !( *this != other );
  }

  inline TOutput operator()(const TInput & A) const
  {
    return static_cast< TOutput >( vcl_cos( static_cast< double >( A ) ) );
  }
};
}
/** \class CosImageFilter
 * \brief Computes the cosine of each pixel.
 *
 * This filter is templated over the pixel type of the input image
 * and the pixel type of the output image.
 *
 * The filter walks over all of the pixels in the input image, and for
 * each pixel does the following:
 *
 * \li cast the pixel value to \c double,
 * \li apply the \c vcl_cos() function to the \c double value,
 * \li cast the \c double value resulting from \c vcl_cos() to the pixel type of the output image,
 * \li store the cast value into the output image.
 *
 * The filter expects both images to have the same dimension (e.g. both
 * 2D, or both 3D, or both ND)
 *
 * \ingroup IntensityImageFilters
 * \ingroup MultiThreaded
 * \ingroup ITKImageIntensity
 */
template< class TInputImage, class TOutputImage >
class ITK_EXPORT CosImageFilter:
  public
  UnaryFunctorImageFilter< TInputImage, TOutputImage,
                           Functor::Cos<
                             typename TInputImage::PixelType,
                             typename TOutputImage::PixelType >   >
{
public:
  /** Standard class typedefs. */
  typedef CosImageFilter Self;
  typedef UnaryFunctorImageFilter<
    TInputImage, TOutputImage,
    Functor::Cos< typename TInputImage::PixelType,
                  typename TOutputImage::PixelType > > Superclass;

  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(CosImageFilter,
               UnaryFunctorImageFilter);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro( InputConvertibleToDoubleCheck,
                   ( Concept::Convertible< typename TInputImage::PixelType, double > ) );
  itkConceptMacro( DoubleConvertibleToOutputCheck,
                   ( Concept::Convertible< double, typename TOutputImage::PixelType > ) );
  /** End concept checking */
#endif

protected:
  CosImageFilter() {}
  virtual ~CosImageFilter() {}

private:
  CosImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &); //purposely not implemented
};
} // end namespace itk

#endif
