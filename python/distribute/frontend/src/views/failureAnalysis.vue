<template>
	<div>
		<div class="container">
			<div class="handle-box">
				<el-select
					v-model="term"
					placeholder="请选择学期"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<el-option key="11" label="第一学年·第一学期" value="11"></el-option>
					<el-option key="12" label="第一学年·第二学期" value="12"></el-option>
					<el-option key="21" label="第二学年·第一学期" value="21"></el-option>
					<el-option key="22" label="第二学年·第二学期" value="22"></el-option>
					<el-option key="31" label="第三学年·第一学期" value="31"></el-option>
					<el-option key="32" label="第三学年·第二学期" value="32"></el-option>
					<el-option key="41" label="第四学年·第一学期" value="41"></el-option>
					<el-option key="42" label="第四学年·第二学期" value="42"></el-option>
				</el-select>
			</div>
			<div class="handle-box">
				<el-select
					v-model="className"
					placeholder="请选择班级"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<el-option
						v-for="cl in classesData"
						:key="cl.value"
						:value="cl.label">
					</el-option>
				</el-select>
				<el-button
					type="primary"
					:icon="Search"
					@click="handleSearchAnalysis(term, className)"
					>搜索</el-button
				>
				<!-- <el-button type="primary" :icon="Plus">新增</el-button> -->
			</div>
			<el-table
				:data="tableTransData"
				border
				class="table"
				ref="multipleTable"
				:row-style="{ height: '100px' }"
				:header-cell-style="{ textAlign: 'center' }"
				:cell-style="{ textAlign: 'center' }"
				:span-method="objectSpanMethod">
				<!-- <el-table-column prop="id" label="ID" width="55" align="center"></el-table-column> -->
				<el-table-column prop="stuName" label="姓名" width="120">
					<!-- <template #default="scope" class="template">
						{{scope.row.courseName}}
						<p class="fail_text">（共计{{scope.row.sumFailedNums}}人次）</p>
					</template> -->
				</el-table-column>
				<el-table-column prop="failSubjectName" label="挂科科目" width="120">
				</el-table-column>
				<el-table-column prop="analysisPerson" label="分析人" width="120">
				</el-table-column>
				<el-table-column prop="content" label="分析内容">
					<!-- <template #default="scope" class="template">
						<CourseLine :chartData="scope.row" />
					</template> -->
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
				</el-table-column>
				<el-table-column prop="address" label="地址"></el-table-column>
				<el-table-column label="状态" align="center">
					<template #default="scope">
						<el-tag
							:type="scope.row.state === '成功' ? 'success' : scope.row.state === '失败' ? 'danger' : ''"
						>
							{{ scope.row.state }}
						</el-tag>
					</template>
				</el-table-column>

				<el-table-column prop="date" label="注册时间"></el-table-column>
				<el-table-column label="操作" width="220" align="center">
					<template #default="scope">
						<el-button text :icon="Edit" @click="handleEdit(scope.$index, scope.row)" v-permiss="15">
							编辑
						</el-button>
						<el-button text :icon="Delete" class="red" @click="handleDelete(scope.$index)" v-permiss="16">
							删除
						</el-button>
					</template>
				</el-table-column> -->
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
		<!-- <el-dialog title="编辑" v-model="editVisible" width="30%">
			<el-form label-width="70px">
				<el-form-item label="用户名">
					<el-input v-model="form.name"></el-input>
				</el-form-item>
				<el-form-item label="地址">
					<el-input v-model="form.address"></el-input>
				</el-form-item>
			</el-form>
			<template #footer>
				<span class="dialog-footer">
					<el-button @click="editVisible = false">取 消</el-button>
					<el-button type="primary" @click="saveEdit">确 定</el-button>
				</span>
			</template>
		</el-dialog> -->
	</div>
</template>

<script setup lang="ts" name="basetable">
import { ref, reactive } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Edit, Search, Plus } from "@element-plus/icons-vue";
import { fetchStudentClassData, fetchAnalysisData } from "../api/index";
import type { TableColumnCtx } from "element-plus/es/components/table/src/table-column/defaults";

interface ClassItem {
	cls_id: number;
	className: string;
}
interface TableItem {
	stuID: string;
	stuName: string;
	stuType: number;
	term: number;
	failSubjectName: string;
	stuClass: string;
	content1: string;
	content2: string;
	content3: string;
	failSubjectNameList: string[];
}
interface TableTransItem {
	stuName: string;
	failSubjectName: string;
	analysisPerson: string;
	content: string;
}
interface ListItem {
	value: number;
	label: string;
}

interface SpanMethodProps {
	row: TableItem;
	column: TableColumnCtx<TableItem>;
	rowIndex: number;
	columnIndex: number;
}

const query = reactive({
	address: "",
	name: "",
	pageIndex: 1,
	pageSize: 10,
});
let term = "11";
let className = "";
const classData = ref<ClassItem[]>([]);
const tableData = ref<TableItem[]>([]);
const tableTransData = ref<TableTransItem[]>([]);
let classesData = ref<ListItem[]>([]);
const pageTotal = ref(0);
// 获取表格数据
const getData = () => {
	// fetchData().then(res => {
	// 	tableData.value = res.data.list;
	// 	pageTotal.value = res.data.pageTotal || 50;
	// 	console.log(tableData.value);
	// });
	fetchStudentClassData().then((res) => {
		classData.value = res.data.data;
		console.log(classData.value);
		classesData.value = [];
		for (var key in classData.value) {
			classesData.value.push({
				value: classData.value[key].cls_id,
				label: classData.value[key].className,
			});
		}
		console.log(classesData);
	});
};
getData();

// 查询操作
const handleSearchAnalysis = (term: String, classesName: String) => {
	console.log("term:" + term);
	console.log("class:" + classesName);
	fetchAnalysisData(term, classesName).then((res) => {
		tableData.value = res.data.data;
		console.log(tableData.value);
		tableTransData.value = [];
		for (var key in tableData.value) {
			tableTransData.value.push({
				stuName: tableData.value[key].stuName,
				failSubjectName: tableData.value[key].failSubjectName,
				analysisPerson: "本人分析",
				content: tableData.value[key].content1,
			});
			tableTransData.value.push({
				stuName: tableData.value[key].stuName,
				failSubjectName: tableData.value[key].failSubjectName,
				analysisPerson: "班长分析",
				content: tableData.value[key].content2,
			});
			tableTransData.value.push({
				stuName: tableData.value[key].stuName,
				failSubjectName: tableData.value[key].failSubjectName,
				analysisPerson: "学委分析",
				content: tableData.value[key].content3,
			});
		}
		console.log(tableTransData.value);
	});
};
// 分页导航
const handlePageChange = (val: number) => {
	query.pageIndex = val;
	getData();
};
const objectSpanMethod = ({
	row,
	column,
	rowIndex,
	columnIndex,
}: SpanMethodProps) => {
	if (columnIndex === 0 || columnIndex === 1) {
		if (rowIndex % 3 === 0) {
			return {
				rowspan: 3,
				colspan: 1,
			};
		} else {
			return {
				rowspan: 0,
				colspan: 0,
			};
		}
	}
};
// // 删除操作
// const handleDelete = (index: number) => {
// 	// 二次确认删除
// 	ElMessageBox.confirm('确定要删除吗？', '提示', {
// 		type: 'warning'
// 	})
// 		.then(() => {
// 			ElMessage.success('删除成功');
// 			tableData.value.splice(index, 1);
// 		})
// 		.catch(() => {});
// };

// // 表格编辑时弹窗和保存
// const editVisible = ref(false);
// let form = reactive({
// 	name: '',
// 	address: ''
// });
// let idx: number = -1;
// const handleEdit = (index: number, row: any) => {
// 	idx = index;
// 	form.name = row.name;
// 	form.address = row.address;
// 	editVisible.value = true;
// };
// const saveEdit = () => {
// 	editVisible.value = false;
// 	ElMessage.success(`修改第 ${idx + 1} 行成功`);
// 	tableData.value[idx].name = form.name;
// 	tableData.value[idx].address = form.address;
// };
</script>

<style scoped>
.handle-box {
	display: inline-block;
	margin-bottom: 20px;
	margin-right: 50px;
}

.handle-select {
	width: 200px;
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

.fail_text {
	color: #ff0000;
	font-size: 10px;
}
</style>
