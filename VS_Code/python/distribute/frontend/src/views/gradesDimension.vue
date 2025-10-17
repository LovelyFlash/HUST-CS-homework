<template style="height: 100%">
  <div style="height: 100%">
    <div class="container" style="height: 92%">
      <div class="handle-box">
        <el-select
          v-model="term"
          placeholder="请选择学期"
          class="handle-select mr10"
          @change="$forceUpdate()"
        >
          <el-option key="11" label="第一学年·第一学期" value="11"></el-option>
          <el-option key="12" label="第一学年·第二学期" value="12"></el-option>
          <el-option key="21" label="第二学年·第一学期" value="21"></el-option>
          <el-option key="22" label="第二学年·第二学期" value="22"></el-option>
          <el-option key="31" label="第三学年·第一学期" value="31"></el-option>
          <el-option key="32" label="第三学年·第二学期" value="32"></el-option>
          <el-option key="41" label="第四学年·第一学期" value="41"></el-option>
          <el-option key="42" label="第四学年·第二学期" value="42"></el-option>
        </el-select>
        <el-button type="primary" @click="getData(term)">搜索</el-button>
      </div>
      <div class="handle-box">
        <el-button type="primary" @click="downloadGradeFile(term)"
          >下载当前学期挂科情况</el-button
        >
        <el-button type="success" @click="downloadYearGradeFile"
          >下载当前学年挂科情况</el-button
        >
      </div>
      <el-table
        :data="tableData"
        border
        class="table"
        ref="multipleTable"
        :row-style="{ height: '500px' }"
        :header-cell-style="{ textAlign: 'center' }"
        :cell-style="{ textAlign: 'center' }"
        style="height: 93%"
      >
        <el-table-column prop="courseName" label="年级" width="10%">
          <template #default="scope" class="template">
            20{{ scope.row.grade }}级
          </template>
        </el-table-column>
        <el-table-column label="各科目挂科情况" width="90%">
          <template #default="scope" class="template">
            <GradeBar :chartData="scope.row" />
          </template>
        </el-table-column>
      </el-table>
    </div>
  </div>
</template>

<script setup lang="ts" name="basetable">
import { ref, reactive } from "vue";
import { ElMessage, ElMessageBox } from "element-plus";
import { Delete, Edit, Search, Plus } from "@element-plus/icons-vue";
import { fetchGradesData, downloadGradeStudentFile } from "../api/index";
import GradeBar from "../components/gradeBar.vue";
import fileDownload from "js-file-download";

interface TableItem {
  courseName: String[];
  failed_nums: number[];
  failed_rates: String[];
  grade: string;
}
interface ListItem {
  value: string;
  label: string;
}

let term = "11";
const tableData = ref<TableItem[]>([]);

const downloadGradeFile = async (term: String) => {
  const gradeList: string[] = JSON.parse(localStorage.getItem("gradeList")!);
  for (var i in gradeList) {
    await downloadGradeStudentFile({ grade: gradeList[i], term: term }).then(
      (res) => {
        fileDownload(res.data, gradeList[i] + "_grade_" + term + "_term.xlsx");
      }
    );
  }
};

// xyk新增：下载当前学年挂科情况
const downloadYearGradeFile = async () => {
  // 获取当前学年第二学期
  // term如"11"->"12", "21"->"22", "31"->"32", "41"->"42"
  let year = term.substring(0, 1);
  let yearTerm = year + "2";
  const gradeList: string[] = JSON.parse(localStorage.getItem("gradeList")!);
  for (var i in gradeList) {
    await downloadGradeStudentFile({
      grade: gradeList[i],
      term: yearTerm,
    }).then((res) => {
      fileDownload(res.data, gradeList[i] + "_grade_" + "_term.xlsx");
    });
  }
};

// 获取表格数据
const getData = (term: String) => {
  fetchGradesData(term)
    .then((res) => {
      console.log(res);
      tableData.value = res.data.data;
      console.log(tableData.value);
    })
    .catch((err) => {
      console.log(err);
    });
};
getData(term);
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

:deep(.el-table__header) {
  width: 100% !important;
}

:deep(.el-table__body) {
  width: 100% !important;
}
</style>
