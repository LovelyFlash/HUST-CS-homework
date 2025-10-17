<template>
  <div ref="courseLineRef" class="chart" id="couLine">
    <!-- <p>{{ fatherDataName }}</p> -->
  </div>
</template>

<script setup lang="ts">
import { onMounted, ref, defineProps, watchEffect } from "vue";
import * as echarts from "echarts";
import "echarts/theme/macarons.js";
import { fetchExcellentBarData } from "../api/index";

const props = defineProps({
  chartData: Object,
});
const courseLineRef = ref<HTMLDivElement>();
onMounted(() => {
  watchEffect(() => {
    let data = props.chartData;
    // console.log(data);

    let gradeDistribute = data?.gradeDistribute;
    let grade = [];
    let series = [];
    for (var key in gradeDistribute) {
      let grade_name = "20" + key + "年";
      grade.push(grade_name);
      let scoreDistribute = gradeDistribute[key];
      let count = [];
      for (var score in scoreDistribute) {
        count.push(scoreDistribute[score]);
      }
      var dict = {
        name: grade_name,
        type: "line",
        smooth: false,
        tooltip: {
          valueFormatter: function (value: string) {
            return value + " 个";
          },
        },
        data: count,
        itemStyle: {
          normal: {
            label: {
              show: true,
              position: "inside",
              textStyle: {
                color: "black",
                fontSize: 12,
              },
              formatter: function (realData: any) {
                return realData.value + "人";
              },
            },
          },
        },
      };
      series.push(dict);
    }
    var app: any = {};
    type EChartsOption = echarts.EChartsOption;

    var chartDom = document.getElementById("couLine")!;
    var myChart = echarts.init(chartDom);
    var option: EChartsOption;

    const posList = [
      "left",
      "right",
      "top",
      "bottom",
      "inside",
      "insideTop",
      "insideLeft",
      "insideRight",
      "insideBottom",
      "insideTopLeft",
      "insideTopRight",
      "insideBottomLeft",
      "insideBottomRight",
    ] as const;

    app.configParameters = {
      rotate: {
        min: -90,
        max: 90,
      },
      align: {
        options: {
          left: "left",
          center: "center",
          right: "right",
        },
      },
      verticalAlign: {
        options: {
          top: "top",
          middle: "middle",
          bottom: "bottom",
        },
      },
      position: {
        options: posList.reduce(function (map, pos) {
          map[pos] = pos;
          return map;
        }, {} as Record<string, string>),
      },
      distance: {
        min: 0,
        max: 100,
      },
    };

    app.config = {
      rotate: 0,
      align: "center",
      verticalAlign: "middle",
      position: "top",
      distance: 15,
      onChange: function () {
        const labelOption: BarLabelOption = {
          rotate: app.config.rotate as BarLabelOption["rotate"],
          align: app.config.align as BarLabelOption["align"],
          verticalAlign: app.config
            .verticalAlign as BarLabelOption["verticalAlign"],
          position: app.config.position as BarLabelOption["position"],
          distance: app.config.distance as BarLabelOption["distance"],
        };
        myChart.setOption<echarts.EChartsOption>({
          series: [
            {
              label: labelOption,
            },
            {
              label: labelOption,
            },
            {
              label: labelOption,
            },
            {
              label: labelOption,
            },
          ],
        });
      },
    };

    type BarLabelOption = NonNullable<echarts.BarSeriesOption["label"]>;

    const labelOption: BarLabelOption = {
      show: true,
      position: app.config.position as BarLabelOption["position"],
      distance: app.config.distance as BarLabelOption["distance"],
      align: app.config.align as BarLabelOption["align"],
      verticalAlign: app.config
        .verticalAlign as BarLabelOption["verticalAlign"],
      rotate: app.config.rotate as BarLabelOption["rotate"],
      formatter: "{c}人  {name|{a}}",
      fontSize: 16,
      rich: {
        name: {},
      },
    };
    // console.log(data);

    var infos = props.chartData?.gradeDistribute;
    // console.log(infos);
    let legends = [];
    let xDatas = [];
    let tempIdx = 0;
    let tempKey = "";
    let tempArray = [];
    let seriesItem = {};
    let seriesData = [];
    for (var key in infos) {
      legends.push(key + "级");
      seriesItem = {};
      tempArray = [];
      for (var k in infos[key]) {
        if (xDatas.indexOf(k) == -1) {
          xDatas.push(k);
        }
        tempArray.push(infos[key][k]);
      }
      seriesItem = {
        name: key + "级",
        type: "line",
        barGap: 0,
        label: labelOption,
        emphasis: {
          focus: "series",
        },
        data: tempArray,
      };
      seriesData.push(seriesItem);
    }
    // console.log(legends);
    // console.log(xDatas);
    // console.log(seriesData);

    option = {
      tooltip: {
        trigger: "axis",
        axisPointer: {
          type: "shadow",
        },
      },
      grid: {
        top: 100,
      },
      legend: {
        show: true,
        data: legends,
        left: "left",
      },
      toolbox: {
        show: true,
        orient: "horizontal",
        left: "right",
        top: "top",
        iconStyle: {
          borderColor: "#2EC7C9",
        },
        feature: {
          mark: { show: true },
          dataView: { show: true, readOnly: false },
          magicType: { show: true, type: ["line", "bar"] },
          restore: { show: true },
          saveAsImage: { show: true },
        },
      },
      xAxis: [
        {
          type: "category",
          name: "分数段",
          nameTextStyle: {
            fontSize: "16",
          },
          axisTick: { show: false },
          data: xDatas,
          axisLabel: {
            formatter: "{value}分",
          },
          axisLine: {
            lineStyle: {
              color: "rgb(59,165,217)",
            },
          },
        },
      ],
      yAxis: [
        {
          type: "value",
          name: "人数",
          minInterval: 1,
          nameTextStyle: {
            fontSize: "16",
          },
          axisLabel: {
            formatter: "{value} 人",
          },
          axisLine: {
            lineStyle: {
              color: "rgb(59,165,217)",
            },
          },
        },
      ],
      series: seriesData,
    };
    // 绘制图表
    option && myChart.setOption(option);
  });
});
</script>
<style scoped>
.chart {
  width: 100%;
  height: 500px;
}
.el-button {
  padding: 0 !important;
}
</style>
