#ifndef NORMALIZE_H_
#define NORMALIZE_H_

#include "alone_net.h"
#include "network.h"

struct normalize_layer;
typedef struct normalize_layer normalize_layer;

struct normalize_layer {
  LAYER_TYPE type;

  float *output;
  float *output_gpu;

  size_t output_size;

  int out_c;
  int out_h;
  int out_w;

  float *scale;
  float *scale_gpu;
  size_t scale_size;

  float *out_norm;
  float *out_norm_gpu;
  size_t out_norm_size;

  float *powed_output;
  float *powed_output_gpu;

  float *ones_channel;
  float *ones_channel_gpu;
  size_t ones_channel_size;

  void (*forward_gpu)(struct normalize_layer, float *input_gpu);
};

normalize_layer make_normalize_layer_gpu(int batch, int out_c, int out_h, int out_w, int scale);
void free_normalize_layer_gpu(normalize_layer sl);
void forward_normalize_gpu(normalize_layer sl, float *input_gpu);
__global__ void pow_kernel(const float *input, float *output, const int size, const float alpha);
__global__ void div_kernel(const float *input, const float *div_input, float *output,
                           const unsigned int size, const int wh);
__global__ void mul_kernel(const float *input, const float *mul_input, float *output,
                           const unsigned int size, const int channel, const int wh);

#endif
