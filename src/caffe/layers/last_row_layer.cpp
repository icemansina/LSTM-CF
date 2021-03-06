#include <vector>
#include "caffe/layers/last_row_layer.hpp"

namespace caffe{

template <typename Dtype>
void LastRowLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
	CHECK_EQ(3, bottom[0]->num_axes());
	vector<int> top_shape(3);

	top_shape[0] = bottom[0]->shape(1);
	top_shape[1] = 1;
	top_shape[2] = bottom[0]->shape(2);

	top[0]->Reshape(top_shape);
	
}

template <typename Dtype>
void LastRowLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
	const Dtype* bottom_data = bottom[0]->cpu_data();
	Dtype* top_data = top[0]->mutable_cpu_data();

	int num = bottom[0]->shape(0);
	int num1 = bottom[0]->shape(1);
	int channels = bottom[0]->shape(2);

	bottom_data += bottom[0]->offset(num - 1);
	caffe_copy(channels * num1, bottom_data, top_data);
}

template <typename Dtype>
void LastRowLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
	const Dtype* top_diff = top[0]->cpu_diff();
	Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();

	int num = bottom[0]->shape(0);
	int num1 = bottom[0]->shape(1);
	int channels = bottom[0]->shape(2);

	bottom_diff += bottom[0]->offset(num - 1);
	caffe_copy(channels * num1, top_diff, bottom_diff);	
}

#ifdef CPU_ONLY
STUB_GPU(LastRowLayer);
#endif

INSTANTIATE_CLASS(LastRowLayer);
REGISTER_LAYER_CLASS(LastRow);

}

