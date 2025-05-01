<template style="height: 100%;">
	<div style="height: 100%;">
		<div class="container" ref="stu_box" style="height: 92%;">
			<div class="handle-box">
				<el-select
					v-model="grade"
					placeholder="请选择年级"
					class="handle-select mr10"
					@change="$forceUpdate()">
					<template v-for="gradeIndex in gradeList">
						<el-option
							:label="'20' + gradeIndex + '级'"
							:value="gradeIndex"></el-option>
					</template>
				</el-select>
				<el-button
					type="primary"
					:icon="Search"
					@click="handleSearchTerm(grade)"
					>搜索</el-button
				>
			</div>
			<div class="handle-box">
				<el-button type="primary" @click="downloadStudentInfo(grade)">下载</el-button>
			</div>
			<!-- <div class="handle-box">
				<el-input
					v-model="studentID"
					placeholder="请输入学号"
					clearable
					class="handle-input mr10"
					@clear="clearOps"></el-input>
				<el-input
					v-model="studentName"
					placeholder="请输入姓名"
					clearable
					class="handle-input mr10"
					@clear="clearOps"></el-input>
				<el-button type="primary" :icon="Search" @click="handleSearchStudent"
					>查询</el-button
				>
			</div> -->
			<div v-loading="loading" style="height: 83%; overflow: scroll">
				<el-row v-for="(item, index) in showData" :key="index">
					<el-col>
						<!-- :data里需要是个数组 所以这里将item用[]进行包裹-->
						<el-table
							:data="[item]"
							border
							class="table"
							ref="multipleTable"
							:header-cell-style="{ textAlign: 'center' }"
							:cell-style="{ textAlign: 'center' }">
							<el-table-column prop="index" label="序号" width="12%">
							</el-table-column>
							<el-table-column prop="stuID" label="学号" width="12%">
							</el-table-column>
							<el-table-column prop="stuName" label="姓名" width="12%">
							</el-table-column>
							<el-table-column prop="stuClass" label="班级" width="12%">
							</el-table-column>
							<el-table-column
								prop="totalWeightedScore"
								label="加权平均"
								width="12%">
							</el-table-column>
							<el-table-column
								prop="failedSubjectNums"
								label="累计不及格科目数"
								width="14%">
							</el-table-column>
							<el-table-column
								prop="sumFailedCreditALL"
								label="累计不及格学分"
								width="15%">
							</el-table-column>
							<el-table-column
								prop="failedSubjectNames"
								label="不及格科目具体名称"
								width="30%">
							</el-table-column>
						</el-table>
						<el-table
							:data="[item]"
							border
							class="table"
							ref="multipleTable"
							:row-style="{ height: '400px' }"
							:header-cell-style="{ textAlign: 'center' }"
							:cell-style="{ textAlign: 'center' }">
							<el-table-column
								prop="totalWeightedScoreTerm,failedSubjectNumsTerm"
								label="个人成绩柱状图">
								<template #default="scope" class="template">
									<StudentInfoBar
										:chartData="{
											totalWeightedScoreTerm: scope.row.totalWeightedScoreTerm,
											failedSubjectNumsTerm: scope.row.failedSubjectNumsTerm,
										}" />
								</template>
							</el-table-column>
							<!-- <el-table-column prop="selfContent" label="个人分析">
								<el-card>
									<template #header>
										<div class="card-header">
											<span>第一学年个人分析</span>
										</div>
									</template>
									<div class="text item analysis" @click="openDialog">
										个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析
									</div>
								</el-card>
								<el-card>
									<template #header>
										<div class="card-header">
											<span>第二学年个人分析</span>
										</div>
									</template>
									<div class="text item analysis" @click="openDialog">
										个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析
									</div>
								</el-card>
								<el-card>
									<template #header>
										<div class="card-header">
											<span>第三学年个人分析</span>
										</div>
									</template>
									<div class="text item analysis" @click="openDialog">
										个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析
									</div>
								</el-card>
								<el-card>
									<template #header>
										<div class="card-header">
											<span>第四学年个人分析</span>
										</div>
									</template>
									<div class="text item analysis" @click="openDialog">
										个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析个人分析
									</div>
								</el-card>
							</el-table-column> -->
						</el-table>
					</el-col>
				</el-row>
			</div>

			<div class="pagination">
				<el-pagination
					background
					layout="total, prev, pager, next"
					v-model:current-page="currentPage"
					:total="pageTotal"
					:page-size="10"
					@current-change="handlePageChange"></el-pagination>
			</div>

			<el-dialog v-model="dialogVisible" title="个人分析" width="30%" draggable>
				<span>这里是个人分析的具体内容！</span>
				<template #footer>
					<span class="dialog-footer">
						<el-button type="primary" @click="dialogVisible = false">
							关闭
						</el-button>
					</span>
				</template>
			</el-dialog>
		</div>
	</div>
</template>

<script setup lang="ts" name="basetable">
import {
	ref,
	reactive,
	onMounted,
	defineProps,
	getCurrentInstance,
	inject,
	watch,
} from "vue";
import { ElMessage, ElMessageBox, ElBacktop } from "element-plus";
import { Delete, Edit, Search, Plus, User } from "@element-plus/icons-vue";
import { fetchStudentInfoData, downloadStudentInfoFileDetail } from "../api/index";
import type { TableColumnCtx } from "element-plus/es/components/table/src/table-column/defaults";
import StudentInfoBar from "../components/studentInfoBar.vue";
import fileDownload from "js-file-download";

interface TableItem {
	stuID: string;
	grade: number;
	stuName: string;
	stuClass: string;
	totalWeightedScore: number;
	failedSubjectNames: string;
	failedSubjectTermNames: string[];
	failedSubjectNums: number;
	sumFailedCreditALL: number;
    totalCreditALL: number;
    sumFailedCreditUnclassified: number;
    totalCreditUnclassified: number;
    sumFailedCreditPublicCompulsory: number;
    totalCreditPublicCompulsory: number;
    sumFailedCreditProfessionalCompulsory: number;
    totalCreditProfessionalCompulsory: number;
    sumFailedCreditProfessionalElective: number;
    totalCreditProfessionalElective: number;
    sumFailedCreditPublicElective: number;
    totalCreditPublicElective: number;
	failedSubjectNumsTerm: number[];
	totalWeightedScoreTerm: number[];
	totalFailedCreditTerm: number[];
	totalCreditExcludePublicElective: number;
    totalCreditIncludePublicElective: number;
    requiredCreditExcludePublicElective: number;
    requiredCreditIncludePublicElective: number;
    excludePublicElectiveType: number;
    includePublicElectiveType: number;
	index: number;
}
interface ListItem {
	value: string;
	label: string;
}

const query = reactive({
	address: "",
	name: "",
	pageIndex: 1,
	pageSize: 10,
});
let grade = "18";
const studentID = ref<string>("");
const studentName = ref<string>("");
const tableData = ref<TableItem[]>([]);
const tableDataCopy = ref<TableItem[]>([]);
let showData = ref<TableItem[]>([]); // 当页需要展示的学生信息数组，根据当前页码计算
let coursesData = ref<ListItem[]>([]);
let pageTotal = ref(0);
const loading = ref(true);
const currentPage = ref(0);
const dialogVisible = ref(false);
const gradeList = ref<string[]>([]);

const getGradeList = () => {
	gradeList.value = JSON.parse(localStorage.getItem("gradeList")!);
	gradeList.value.sort((a, b) => {
		return Number(a) - Number(b);
	});
	grade = gradeList.value[0];
};

getGradeList();

const cmp = (a: TableItem, b: TableItem) => {
	if (a.failedSubjectNums == b.failedSubjectNums)
		return b.sumFailedCreditALL - a.sumFailedCreditALL;
	return b.failedSubjectNums - a.failedSubjectNums;
};
// 获取表格数据
const getData = (grade: String) => {
	fetchStudentInfoData(grade).then((res) => {
		console.log(res);
		studentID.value = "";
		studentName.value = "";
		loading.value = false;
		if (res.data.code == 200) {
			tableData.value = res.data.data;
			tableData.value.sort(cmp)
			for (var i in tableData.value)
				tableData.value[i].index = Number(i) + 1;
			currentPage.value = 1;
			pageTotal.value = tableData.value.length;
			showData.value = tableData.value.slice(0, 10);
			tableDataCopy.value = tableData.value;
			console.log(tableData.value);
			console.log(showData.value);
		}
	});
};
getData(grade);

// 根据年级查询操作
const handleSearchTerm = (grade: String) => {
	query.pageIndex = 1;
	console.log("term:" + grade);
	getData(grade);
};
// const handleSearchStudent = () => {
// 	// 根据学生信息查询
// 	studentID.value = studentID.value.replace(/\s/g, "");
// 	studentName.value = studentName.value.replace(/\s/g, "");
// 	console.log("studentID:" + studentID.value);
// 	console.log("studentName:" + studentName.value);
// 	tableData.value = tableDataCopy.value;
// 	tableData.value = tableData.value.filter((item) => {
// 		return (
// 			item.stuID.indexOf(studentID.value) != -1 &&
// 			item.stuName.indexOf(studentName.value) != -1
// 		);
// 	});
// 	console.log(tableData.value);
// 	currentPage.value = 1;
// 	pageTotal.value = tableData.value.length;
// 	showData.value = tableData.value.slice(0, 10);
// };
// const clearOps = () => {
// 	handleSearchStudent();
// };
const scrollToTop = () => {
	window.scrollTo({ top: 0, left: 0, behavior: "smooth" });
};
// 分页导航
const handlePageChange = (val: number) => {
	console.log(val);
	showData.value = tableData.value.slice((val - 1) * 10, (val - 1) * 10 + 10);
	// console.log(stu_box.value?.scrollTop);

	// window.scrollTo(0,0);
	// scrollToTop();
};

const openDialog = () => {
	dialogVisible.value = true;
};

const downloadStudentInfo = async (grade: string) => {
	// console.log(grade)
	await downloadStudentInfoFileDetail({ grade: grade }).then((res) => {
		// console.log(res)
		fileDownload(res.data, grade + "_grade_studentInfo_detail.xlsx")
	}).catch((err) => {
		console.log(err)
	})
}
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
.card-header {
	display: flex;
	justify-content: space-between;
	align-items: center;
}

.text {
	font-size: 14px;
}

.item {
	padding: 8px 0;
}

.analysis {
	cursor: pointer;
}

:deep(.el-table__header)  {
	width: 100% !important;
}

:deep(.el-table__body)  {
	width: 100% !important;
}
</style>
