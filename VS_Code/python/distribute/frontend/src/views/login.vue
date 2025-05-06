<template>
	<div class="login-wrap">
		<div class="ms-login">
			<div class="ms-title">学业分析系统</div>
			<el-form :model="loginForm" :rules="rules" ref="loginFormRef" label-width="0px" class="ms-content">
				<el-form-item prop="username">
					<el-input v-model="loginForm.username" placeholder="用户名">
						<template #prepend>
							<el-button :icon="User"></el-button>
						</template>
					</el-input>
				</el-form-item>
				<el-form-item prop="password">
					<el-input type="password" placeholder="密码" v-model="loginForm.password"
						@keyup.enter="submitForm(loginFormRef)" show-password>
						<template #prepend>
							<el-button :icon="Lock"></el-button>
						</template>
					</el-input>
				</el-form-item>
				<div class="login-btn">
					<el-button type="primary" @click="submitForm(loginFormRef)">登录</el-button>
				</div>
				<!-- <p class="login-tips">
					管理员用户名：admin,密码：123123<br>
					普通用户名：test4,密码：123456</p> -->
			</el-form>
		</div>
	</div>
</template>

<script setup lang="ts">
import { ref, reactive } from 'vue';
import { useTagsStore } from '../store/tags';
import { usePermissStore } from '../store/permiss';
import { useRouter } from 'vue-router';
import { ElMessage } from 'element-plus';
import type { FormInstance, FormRules } from 'element-plus';
import { Lock, User } from '@element-plus/icons-vue';
import { login } from '../api/index'

// 规范数据类型
interface LoginInfo {
	username: string;
	password: string;
	grant_type:string;
	scope:string;
	client_id:string;
	client_secret:string;
};
const router = useRouter();
const loginForm = reactive<LoginInfo>({
	username: '',
	password: '',
	grant_type:'',
	scope:'',
	client_id:'',
	client_secret:''
});
const rules: FormRules = {
	username: [
		{
			required: true,
			message: '请输入用户名',
			trigger: 'blur'
		}
	],
	password: [{ required: true, message: '请输入密码', trigger: 'blur' }]
};
const permiss = usePermissStore();
const loginFormRef = ref<FormInstance>();
const submitForm = (formEl: FormInstance | undefined) => {
	if (!formEl) return;
	formEl.validate((valid: boolean) => {
		if (valid) {
			login(loginForm).then(res=>{
				console.log(res);
				if(res.data.code == 200)
				{
					localStorage.setItem('token',res.data.access_token)
					localStorage.setItem('ms_username', loginForm.username);
					localStorage.setItem('is_superuser', res.data.data.is_superuser);
					const keys = permiss.defaultList[res.data.data.is_superuser == true ? 'admin' : 'user'];
					permiss.handleSet(keys);
					localStorage.setItem('ms_keys', JSON.stringify(keys))
					router.push('/')
					ElMessage.success('登录成功')
				} else
				ElMessage.error('密码错误或用户名不存在');
			});
		} else {
			console.log("!!!!")
			ElMessage.error('登录失败');
			return false;
		}
	});
};

const tags = useTagsStore();
tags.clearTags();
</script>

<style scoped>
.login-wrap {
	position: relative;
	width: 100%;
	height: 100%;
	background-image: url(../assets/img/login-bg.jpg);
	background-size: 100%;
}

.ms-title {
	width: 100%;
	line-height: 50px;
	text-align: center;
	font-size: 20px;
	color: #fff;
	border-bottom: 1px solid #ddd;
}

.ms-login {
	position: absolute;
	left: 50%;
	top: 50%;
	width: 350px;
	margin: -190px 0 0 -175px;
	border-radius: 5px;
	background: rgba(255, 255, 255, 0.3);
	overflow: hidden;
}

.ms-content {
	padding: 30px 30px;
}

.login-btn {
	text-align: center;
}

.login-btn button {
	width: 100%;
	height: 36px;
	margin-bottom: 10px;
}

.login-tips {
	font-size: 12px;
	line-height: 30px;
	color: #fff;
}
</style>
