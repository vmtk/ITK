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
#ifndef __itkInverseDeconvolutionImageFilter_hxx
#define __itkInverseDeconvolutionImageFilter_hxx

#include "itkInverseDeconvolutionImageFilter.h"

#include "itkBinaryFunctorImageFilter.h"

namespace itk
{

template< class TInputImage, class TKernelImage, class TOutputImage, class TInternalPrecision >
InverseDeconvolutionImageFilter< TInputImage, TKernelImage, TOutputImage, TInternalPrecision >
::InverseDeconvolutionImageFilter()
{
  m_KernelZeroMagnitudeThreshold = 1.0e-4;
}

template< class TInputImage, class TKernelImage, class TOutputImage, class TInternalPrecision >
void
InverseDeconvolutionImageFilter< TInputImage, TKernelImage, TOutputImage, TInternalPrecision >
::GenerateData()
{
  // Create a process accumulator for tracking the progress of this
  // minipipeline
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New();
  progress->SetMiniPipelineFilter( this );

  typename InputImageType::Pointer localInput = InputImageType::New();
  localInput->Graft( this->GetInput() );

  const KernelImageType* kernelImage = this->GetKernelImage();

  InternalComplexImagePointerType input = NULL;
  InternalComplexImagePointerType kernel = NULL;

  this->PrepareInputs( localInput, kernelImage, input, kernel, progress, 0.7 );

  typedef Functor::InverseDeconvolutionFunctor< InternalComplexType,
                                                InternalComplexType,
                                                InternalComplexType> FunctorType;
  typedef BinaryFunctorImageFilter< InternalComplexImageType,
                                    InternalComplexImageType,
                                    InternalComplexImageType, FunctorType > InverseFilterType;
  typename InverseFilterType::Pointer inverseFilter = InverseFilterType::New();
  inverseFilter->SetInput1( input );
  inverseFilter->SetInput2( kernel );
  inverseFilter->ReleaseDataFlagOn();

  typename InverseFilterType::FunctorType & inverseFunctor = inverseFilter->GetFunctor();
  inverseFunctor.SetKernelZeroMagnitudeThreshold( this->GetKernelZeroMagnitudeThreshold() );
  progress->RegisterInternalFilter( inverseFilter, 0.1 );

  // Free up the memory for the prepared inputs
  input = NULL;
  kernel = NULL;

  this->ProduceOutput( inverseFilter->GetOutput(), progress, 0.2 );
}

template< class TInputImage, class TKernelImage, class TOutputImage, class TInternalPrecision >
void
InverseDeconvolutionImageFilter< TInputImage, TKernelImage, TOutputImage, TInternalPrecision >
::PrintSelf(std::ostream &os, Indent indent) const
{
  this->Superclass::PrintSelf( os, indent );

  os << indent << "KernelZeroMagnitudeThreshold: " << m_KernelZeroMagnitudeThreshold << std::endl;
}

}  // end namespace itk
#endif
