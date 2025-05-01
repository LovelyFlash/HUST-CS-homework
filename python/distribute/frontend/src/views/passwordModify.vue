<template>
	<div class="container">
		<div class="form-box">
			<el-form ref="formRef" :rules="rules" :model="form" label-width="80px">
				<el-form-item label="原密码" prop="name">
					<el-input v-model="form.name"></el-input>
				</el-form-item>
				<el-form-item label="新密码" prop="name">
					<el-input v-model="form.name"></el-input>
				</el-form-item>
				<el-form-item label="重复密码" prop="name">
					<el-input v-model="form.name"></el-input>
				</el-form-item>
				<el-form-item>
					<el-button type="primary" @click="onSubmit(formRef)">保存</el-button>
					<el-button @click="onReset(formRef)">重置</el-button>
				</el-form-item>
			</el-form>
		</div>
	</div>
</template>

<script setup lang="ts" name="baseform">
import { reactive, ref } from 'vue';
import { ElMessage } from 'element-plus';
import type { FormInstance, FormRules } from 'element-plus';

const rules: FormRules = {
	name: [{ required: true, message: '内容不能为空', trigger: 'blur' }]
};
const formRef = ref<FormInstance>();
const form = reactive({
	name: '',
	region: '',
	date1: '',
	date2: '',
	delivery: true,
	type: ['步步高'],
	resource: '小天才',
	desc: '',
	options: []
});
// 提交
const onSubmit = (formEl: FormInstance | undefined) => {
	// 表单校验
	if (!formEl) return;
	formEl.validate(valid => {
		if (valid) {
			console.log(form);
			ElMessage.success('提交成功！');
		} else {
			return false;
		}
	});
};
// 重置
const onReset = (formEl: FormInstance | undefined) => {
	if (!formEl) return;
	formEl.resetFields();
};
</script>
