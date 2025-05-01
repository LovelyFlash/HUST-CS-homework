<template>
	<div>
		<div class="container">
			<div class="handle-box">
				<el-input
					v-model="query.name"
					placeholder="用户名"
					class="handle-input mr10"></el-input>
				<el-button type="primary" :icon="Search" @click="handleSearch"
					>搜索</el-button
				>
				<el-button type="primary" :icon="Plus" @click="handleAdd"
					>新增用户</el-button
				>
			</div>
			<el-table :data="tableData" border class="table" ref="multipleTable">
				<el-table-column prop="id" label="ID" width="55" align="center">
					<template #default="scope">{{ scope.$index + 1 }}</template>
				</el-table-column>
				<el-table-column label="用户名">
					<template #default="scope">{{ scope.row.cName }}</template>
				</el-table-column>
				<el-table-column label="工号">
					<template #default="scope">{{ scope.row.cID }}</template>
				</el-table-column>
				<!-- <el-table-column label="头像(查看大图)" align="center">
					<template #default="scope">
						<el-image
							class="table-td-thumb"
							:src="scope.row.thumb"
							:z-index="10"
							:preview-src-list="[scope.row.thumb]"
							preview-teleported
						>
						</el-image>
					</template>
				</el-table-column> -->
				<el-table-column label="状态" align="center">
					<template #default="scope">
						<el-tag
							:type="
								scope.row.is_active === true
									? 'success'
									: scope.row.is_active === false
									? 'danger'
									: ''
							">
							{{
								scope.row.is_active === true
									? "可用"
									: scope.row.is_active === false
									? "禁用"
									: ""
							}}
						</el-tag>
					</template>
				</el-table-column>
				<el-table-column label="操作" width="220" align="center">
					<template #default="scope">
						<el-button
							text
							:icon="Edit"
							@click="handleEdit(scope.$index, scope.row)"
							v-permiss="15">
							编辑
						</el-button>
						<el-button
							text
							:icon="Delete"
							class="red"
							@click="handleDelete(scope.$index)"
							v-permiss="16">
							删除
						</el-button>
					</template>
				</el-table-column>
			</el-table>
			<div class="pagination">
				<el-pagination
					background
					layout="total, prev, pager, next"
					:current-page="query.pageIndex"
					:page-size="query.pageSize"
					:total="pageTotal"
					@current-change="handlePageChange"></el-pagination>
			</div>
		</div>

		<!-- 编辑弹出框 -->
		<el-dialog title="编辑" v-model="editVisible" width="30%">
			<el-form label-width="70px">
				<el-form-item label="状态：">
					<el-radio-group v-model="form.is_active" class="ml-4">
						<el-radio :label="true" size="large">可用</el-radio>
						<el-radio :label="false" size="large">禁用</el-radio>
					</el-radio-group>
				</el-form-item>
				<el-form-item label="权限：">
					<el-radio-group v-model="form.is_superuser" class="ml-4">
						<el-radio :label="true" size="large">管理员</el-radio>
						<el-radio :label="false" size="large">普通用户</el-radio>
					</el-radio-group>
				</el-form-item>
			</el-form>
			<template #footer>
				<span class="dialog-footer">
					<el-button @click="editVisible = false">取 消</el-button>
					<el-button type="primary" @click="editUser">确 定</el-button>
				</span>
			</template>
		</el-dialog>
		<!-- 添加用户弹出框 -->
		<el-dialog title="添加用户" v-model="addVisible" width="30%">
			<el-form label-width="70px">
				<el-form-item label="工号">
					<el-input v-model="form.cID"></el-input>
				</el-form-item>
				<el-form-item label="用户名">
					<el-input v-model="form.cName"></el-input>
				</el-form-item>
				<el-form-item label="密码">
					<el-input v-model="form.password"></el-input>
				</el-form-item>
			</el-form>
			<template #footer>
				<span class="dialog-footer">
					<el-button @click="addVisible = false">取 消</el-button>
					<el-button type="primary" @click="addUser">确 定</el-button>
				</span>
			</template>
		</el-dialog>
	</div>
</template>

<script setup lang="ts" name="basetable">
import { ref, reactive } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Edit, Search, Plus } from "@element-plus/icons-vue";
import { fetchUsersData, addUserData } from "../api/index";

interface TableItem {
	cID: string;
	cName: string;
	is_active: boolean;
	is_superuser: boolean;
}

interface AddUserItem {
	cID: string;
	cName: string;
	is_active: boolean;
	is_superuser: boolean;
	password: string;
}

const query = reactive({
	address: "",
	name: "",
	pageIndex: 1,
	pageSize: 10,
});
const tableData = ref<TableItem[]>([]);
const pageTotal = ref(0);
// 获取表格数据
const getData = () => {
	fetchUsersData().then((res) => {
		tableData.value = res.data;
		console.log(tableData.value);

		// pageTotal.value = res.data.pageTotal || 50;
	});
};
getData();

// 查询操作
const handleSearch = () => {
	query.pageIndex = 1;
	getData();
};
// 分页导航
const handlePageChange = (val: number) => {
	query.pageIndex = val;
	getData();
};

// 删除操作
const handleDelete = (index: number) => {
	// 二次确认删除
	ElMessageBox.confirm("确定要删除吗？", "提示", {
		type: "warning",
	})
		.then(() => {
			ElMessage.success("删除成功");
			tableData.value.splice(index, 1);
		})
		.catch(() => {});
};

// 表格编辑时弹窗和保存
const editVisible = ref(false);
let form = reactive<AddUserItem>({
	cID: "",
	cName: "",
	//默认情况下时可用、非超级用户
	is_active: true,
	is_superuser: false,
	password: "",
});
let idx: number = -1;
const handleEdit = (index: number, row: any) => {
	idx = index;
	form.name = row.name;
	form.address = row.address;
	editVisible.value = true;
};
const editUser = () => {
	editVisible.value = false;
	ElMessage.success(`修改第 ${idx + 1} 行成功`);
	tableData.value[idx].name = form.name;
	tableData.value[idx].address = form.address;
};
// 增加用户时弹窗和保存
const addVisible = ref(false);
const handleAdd = () => {
	addVisible.value = true;
};
const addUser = () => {
	addVisible.value = false;
	addUserData(form).then((res) => {
		console.log(res.data.msg);
		ElMessage.success(`添加用户成功`);
		getData();
	});
};
</script>

<style scoped>
.handle-box {
	margin-bottom: 20px;
}

.handle-select {
	width: 120px;
}

.handle-input {
	width: 300px;
}
.table {
	width: 100%;
	font-size: 14px;
}
.red {
	color: #ff0000;
}
.mr10 {
	margin-right: 10px;
}
.table-td-thumb {
	display: block;
	margin: auto;
	width: 40px;
	height: 40px;
}
</style>
