<template>
	<div class="sidebar">
		<el-menu class="sidebar-el-menu" :default-active="onRoutes" :collapse="sidebar.collapse"
			background-color="#324157" text-color="#bfcbd9" active-text-color="#20a0ff" unique-opened router>
			<template v-for="item in items">
				<template v-if="item.subs">
					<el-sub-menu :index="item.index" :key="item.index" v-permiss="item.permiss">
						<template #title>
							<el-icon>
								<component :is="item.icon"></component>
							</el-icon>
							<span>{{ item.title }}</span>
						</template>
						<template v-for="subItem in item.subs">
							<el-sub-menu v-if="subItem.subs" :index="subItem.index" :key="subItem.index"
								v-permiss="item.permiss">
								<template #title>{{ subItem.title }}</template>
								<el-menu-item v-for="(threeItem, i) in subItem.subs" :key="i" :index="threeItem.index">
									{{ threeItem.title }}
								</el-menu-item>
							</el-sub-menu>
							<el-menu-item v-else :index="subItem.index" v-permiss="item.permiss">
								{{ subItem.title }}
							</el-menu-item>
						</template>
					</el-sub-menu>
				</template>
				<template v-else-if="item.permiss!='3' || is_superuser == true">
					<el-menu-item :index="item.index" :key="item.index" v-permiss="item.permiss">
						<el-icon>
							<component :is="item.icon"></component>
						</el-icon>
						<!-- <i class="el-icon-lx-edit"></i> -->
						<template #title>{{ item.title }}</template>
					</el-menu-item>
				</template>
			</template>
		</el-menu>
	</div>
</template>

<script setup lang="ts">
import { computed } from 'vue';
import { useSidebarStore } from '../store/sidebar';
import { useRoute } from 'vue-router';
import { TurnOff } from '@element-plus/icons-vue';

const items = [
	{
		icon: 'Edit',
		index: '3',
		title: '账号管理',
		permiss: '20',
		subs: [
			{
				index: '/usersManagement',
				title: '用户管理',
				permiss: '6'
			},
			{
				index: '/passwordModify',
				title: '修改密码',
				permiss: '6'
			}
		]
	},{
		icon: 'HomeFilled',
		index: '/dashboard',
		title: '系统首页',
		permiss: '1'
	},{
		icon: 'Menu',
		index: '/dashboard',
		title: '课程考试情况',
		permiss: '1',
		subs: [
			{
				index: '/excellent',
				title: '优良学风班',
				permiss: '1'
			},{
				index: '/courseDimension',
				title: '课程维度',
				permiss: '1'
			}, {
				index: '/gradesDimension',
				title: '年级维度',
				permiss: '1'
			}, {
				index: '/classesDimension',
				title: '班级维度',
				permiss: '1'
			},{
				index: '/majorDimension',
				title: '专业维度',
				permiss: '1'
			},
			{
				index: '/scoreDimension',
				title: '分数维度',
				permiss: '1'
			},
			// {
			// 	index: '4',
			// 	title: '三级菜单',
			// 	permiss: '7',
			// 	subs: [
			// 		{
			// 			index: '/editor',
			// 			title: '富文本编辑器',
			// 			permiss: '8'
			// 		},
			// 		{
			// 			index: '/markdown',
			// 			title: 'markdown编辑器',
			// 			permiss: '9'
			// 		}
			// 	]
			// }
		]
	},{
		icon: 'Notebook',
		index: '/studentInformation',
		title: '学生信息',
		permiss: '1'
	},{
		icon: 'Memo',
		index: '/studentInformationS',
		title: '学生信息(精简)',
		permiss: '1'
	}, {
		icon: 'DataAnalysis',
		index: '/failureAnalysis',
		title: '不及格分析',
		permiss: '1'
	},
	{
		icon: 'UploadFilled',
		index: '/filesUpload',
		title: '文件上传',
		permiss: '4'
	}
	// {
	// 	icon: 'Calendar',
	// 	index: '/table',
	// 	title: '基础表格',
	// 	permiss: '2'
	// },
	// {
	// 	icon: 'DocumentCopy',
	// 	index: '/tabs',
	// 	title: 'tab选项卡',
	// 	permiss: '3'
	// },
	// {
	// 	icon: 'Setting',
	// 	index: '/icon',
	// 	title: '自定义图标',
	// 	permiss: '10'
	// },
	// {
	// 	icon: 'PieChart',
	// 	index: '/charts',
	// 	title: 'schart图表',
	// 	permiss: '11'
	// },
	// {
	// 	icon: 'Warning',
	// 	index: '/permission',
	// 	title: '权限管理',
	// 	permiss: '13'
	// },
	// {
	// 	icon: 'CoffeeCup',
	// 	index: '/donate',
	// 	title: '支持作者',
	// 	permiss: '14'
	// }
];
const is_superuser = localStorage.getItem('is_superuser') === true ? true : false

const route = useRoute();
const onRoutes = computed(() => {
	return route.path;
});

const sidebar = useSidebarStore();
</script>

<style scoped>
.sidebar {
	display: block;
	position: absolute;
	left: 0;
	top: 70px;
	bottom: 0;
	overflow-y: scroll;
}

.sidebar::-webkit-scrollbar {
	width: 0;
}

.sidebar-el-menu:not(.el-menu--collapse) {
	width: 250px;
}

.sidebar>ul {
	height: 100%;
}
</style>
