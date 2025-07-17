<template  style="height: 100%;">
	<div  style="height: 100%;">
		<div class="container" ref="stu_box"  style="height: 92%; width: 95%;">
			<div class="handle-box">
				<el-select
					v-model="grade"
					placeholder="请选择年级"
					class="handle-select mr10"
					style="width: 125px"
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
					@click="handleSearch(grade)"
					>搜索</el-button
				>
			</div>
			<div class="handle-box">
				红牌
				<el-switch
					v-model="showRed"
					active-color="red"
					@change="updateData()"></el-switch>
			</div>
			<div class="handle-box">
				黄牌
				<el-switch
					v-model="showYellow"
					active-color="yellow"
					@change="updateData()"></el-switch>
			</div>
			<div class="handle-box">
				普通
				<el-switch v-model="showWhite" @change="updateData()"></el-switch>
			</div>
			<div class="handle-box">
				大于等于
				<el-select
					v-model="failNums"
					placeholder="不及格科目数"
					style="width: 65px"
					class="handle-select mr10"
					@change="updateData()">
					<div>
						<el-option :key="1" :label="1" :value="1"></el-option>
						<el-option :key="3" :label="3" :value="3"></el-option>
						<el-option :key="5" :label="5" :value="5"></el-option>
						<el-option :key="10" :label="10" :value="10"></el-option>
					</div>
				</el-select>
				科不及格
			</div>
			<!-- <div class="handle-box">
				包含人文选修
				<el-switch v-model="calculateType" @change="changeType()"></el-switch>
				排除人文选修
			</div> -->
			<div class="handle-box">
				<el-button type="primary" @click="downloadStudentInfo(grade)">下载</el-button>
			</div>
			<div style="height: 93%; width: 100%;">
				<el-table
					:data="showData"
					border
					height="100%"
					class="table"
					ref="multipleTable"
					:header-cell-style="{ textAlign: 'center' }"
					:cell-style="{ textAlign: 'center' }"
					:row-style="rowClassStyle">
					<el-table-column type="expand" width="3%">
						<template v-slot="props">
							<el-form label-position="center" inline>
								<el-form-item label="不及格科目具体名称(必修)">
									<span>{{ props.row.failedSubjectNames }}</span>
								</el-form-item>
							</el-form>
						</template>
					</el-table-column>
					<el-table-column type="index" label="序号" width="6%">
					</el-table-column>
					<el-table-column prop="stuID" label="学号" width="12%">
					</el-table-column>
					<el-table-column prop="stuName" label="姓名" width="12%">
					</el-table-column>
					<el-table-column prop="stuClass" label="班级" width="10%">
					</el-table-column>
					<el-table-column
						prop="totalWeightedScore"
						label="加权平均"
						width="12%">
					</el-table-column>
					<el-table-column
						prop="totalCreditExcludePublicElective"
						label="已修学分(总)"
						width="12%">
					</el-table-column>
					<el-table-column
						label="已修学分(必修)"
						width="12%">
						<template v-slot="props">
							{{ props.row.totalCreditPublicCompulsory + props.row.totalCreditProfessionalCompulsory }}
						</template>
					</el-table-column>
					<el-table-column
						prop="totalCreditProfessionalElective"
						label="已修学分(专选)"
						width="12%">
					</el-table-column>
					<el-table-column
						prop="failedSubjectNums"
						label="累计不及格科目数(必修)"
						width="12%">
					</el-table-column>
				</el-table>
			</div>
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
import { fetchStudentInfoData, fetchStudentInfoConfig, downloadStudentInfoFile } from "../api/index";
import type { TableColumnCtx } from "element-plus/es/components/table/src/table-column/defaults";
import StudentInfoBar from "../components/studentInfoBar.vue";
import fileDownload from "js-file-download";
import { time } from "echarts";


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


let grade = "";
const studentID = ref<string>("");
const studentName = ref<string>("");
const tableData = ref<TableItem[]>([]);
const showData = ref<TableItem[]>([]);
const redItem = ref<TableItem[]>([]);
const yellowItem = ref<TableItem[]>([]);
const whiteItem = ref<TableItem[]>([]);
const unclassifiedItem = ref<TableItem[]>([]);
const showRed = ref<boolean>(true);
const showYellow = ref<boolean>(true);
const showWhite = ref<boolean>(true);
const loading = ref(true);
const gradeList = ref<string[]>([]);
let failNums = ref<number>(1);
const calculateType = ref<boolean>(true)

const getGradeList = () => {
	gradeList.value = JSON.parse(localStorage.getItem("gradeList")!);
	gradeList.value.sort((a, b) => {
		return Number(a) - Number(b);
	});
	grade = gradeList.value[0];
};

getGradeList();

const downloadStudentInfo = async (grade: string) => {
	// console.log(grade)
	await downloadStudentInfoFile({ grade: grade, red: showRed.value, yellow: showYellow.value, white: showWhite.value, type: calculateType.value }).then((res) => {
		// console.log(res)
		fileDownload(res.data, grade + "_grade_studentInfo.xlsx")
	}).catch((err) => {
		console.log(err)
	})
}

const cmp = (a: TableItem, b: TableItem) => {
	if (a.failedSubjectNums == b.failedSubjectNums)
		return b.sumFailedCreditALL - a.sumFailedCreditALL;
	return b.failedSubjectNums - a.failedSubjectNums;
};

const setShow = () => {
	showData.value = [];
	if (showRed.value)
		showData.value = showData.value.concat(redItem.value);
	if (showYellow.value)
		showData.value = showData.value.concat(yellowItem.value);
	if (showWhite.value)
		showData.value = showData.value.concat(whiteItem.value);
	showData.value = showData.value.concat(unclassifiedItem.value);
	return;
};

const selectShow = () => {
	var templateArray: TableItem[] = showData.value;
	showData.value = [];
	for (var i in templateArray)
		if (templateArray[i].failedSubjectNums >= failNums.value) showData.value.push(templateArray[i]);
};

const changeType = () => {
	classify();
	setShow();
	selectShow();
}

const updateData = () => {
	setShow();
	selectShow();
};

const classify = () => {
	redItem.value = [];
	yellowItem.value = [];
	whiteItem.value = [];
	unclassifiedItem.value = [];
	for (var i = 0; i < tableData.value.length; i++) {
		if (calculateType.value == true) {
			if (tableData.value[i].excludePublicElectiveType == 3) {
				redItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].excludePublicElectiveType == 2) {
				yellowItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].excludePublicElectiveType == 1) {
				whiteItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].excludePublicElectiveType == 0) {
				unclassifiedItem.value.push(tableData.value[i]);
				continue;
			}
		}
		else {
			if (tableData.value[i].includePublicElectiveType == 3) {
				redItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].includePublicElectiveType == 2) {
				yellowItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].includePublicElectiveType == 1) {
				whiteItem.value.push(tableData.value[i]);
				continue;
			}
			if (tableData.value[i].includePublicElectiveType == 0) {
				unclassifiedItem.value.push(tableData.value[i]);
				continue;
			}
		}
	}
}

// 获取表格数据
const getData = async (grade: String) => {
	await fetchStudentInfoData(grade).then((res) => {
		console.log(res);

		studentID.value = "";
		studentName.value = "";
		loading.value = false;
		if (res.data.code == 200) {
			tableData.value = res.data.data.sort(cmp);
			classify()
			setShow();
			failNums.value = 1;
			selectShow();
		}
	});
};
getData(grade);

// 根据年级查询操作
const handleSearch = (grade: String) => {
	getData(grade);
};

const rowClassStyle = ({ row, _ }) => {
	if (calculateType.value == true) {
			if (row.excludePublicElectiveType == 3) {
				return { background: "rgba(255, 22, 22, 0.771)" };
			}
			if (row.excludePublicElectiveType == 2) {
				return { background: "rgba(249, 239, 42, 0.771)" };
			}
			if (row.excludePublicElectiveType == 1) {
				return { background: "white" };
			}
			if (row.excludePublicElectiveType == 0) {
				return { background: "rgba(140, 146, 172, 0.771)" };
			}
		}
		else {
			if (row.includePublicElectiveType == 3) {
				return { background: "rgba(255, 22, 22, 0.771)" };
			}
			if (row.includePublicElectiveType == 2) {
				return { background: "rgba(249, 239, 42, 0.771)" };
			}
			if (row.includePublicElectiveType == 1) {
				return { background: "white" };
			}
			if (row.includePublicElectiveType == 0) {
				return { background: "rgba(140, 146, 172, 0.771)" };
			}
		}
};
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

:deep(.el-form-item__label)  {
	width: auto;
    color: #99a9bf;
	/* border: 5px;
	margin: 5px; */
	align-self: center !important;
}

:deep(.el-table__header)  {
	width: 100% !important;
}

:deep(.el-table__body)  {
	width: 100% !important;
}
/* :deep(.el-input)  {
	width: 150px !important;
} */

.testColor {
	background-color: rgba(rgba(255, 22, 22, 0.477), rgb(65, 65, 65), blue, alpha);
}
</style>
