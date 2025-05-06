<template>
    <div ref="gradeBarRef" class="chart">
        <!-- <p>{{ fatherDataName }}</p> -->
    </div>
</template>

<script setup lang="ts">
import { onMounted, ref, defineProps, watchEffect } from 'vue';
import * as echarts from 'echarts';
import 'echarts/theme/macarons.js';

const props = defineProps({
    chartData: Object,
});
const gradeBarRef = ref<HTMLDivElement>()
onMounted(() => {
    watchEffect(()=>{
        console.log('props.chartData:', props.chartData);
        let data = props.chartData;
        console.log(props.chartData);
        
        let courseNameList = data?.courseName;
        let courseNameListCopy = courseNameList;
        let normalCourses = [];
        for (let i=0;i<courseNameListCopy.length;i += 1) {
            // console.log(courseNameListCopy[i]);
            let courseArr = "";
            for (var j=0;j<courseNameListCopy[i].length;j++) {
                // console.log(courseNameListCopy[i][j]);
                if (courseNameListCopy[i][j] == '︵') {
                    courseArr += '（';
                } else if (courseNameListCopy[i][j] == '︶') {
                    courseArr += '）';
                } else {
                    courseArr += courseNameListCopy[i][j];
                }
            }
            normalCourses.push(courseArr);
        }
        console.log(normalCourses);
        
        
        let failedNum = data?.failed_nums;
        let failedRate = data?.failed_rates;
        // 基于准备好的dom，初始化echarts实例
        var myChart = echarts.init(gradeBarRef.value as HTMLDivElement, 'macarons');
        var option = {
            tooltip: {
                trigger: 'axis',
                backgroundColor: '#fff',
                axisPointer: {
                    type: 'cross',
                    crossStyle: {
                        color: '#999'
                    }
                }
            },
            toolbox: {
                feature: {
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['line', 'bar'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },
            grid: {
                top: 100,
            },
            legend: {
                data: ['挂科人数', '不及格比例']
            },
            xAxis: [
                {
                    type: 'category',
                    data: normalCourses,
                    // data: courseNameList,
                    axisPointer: {
                        type: 'shadow'
                    },
                    axisLabel: {
                        show: true,
                        interval: 0,
                        grid: {left:'10%', bottom:'35%'},
                        // interval:0,
                        // rotate:90,//倾斜度 -90 至 90 默认为0
                        // margin:5,
                        //  让x轴文字方向为竖向
                        // formatter: function (value: string) {
                        //     return value.split('').join('\n')
                        // }
                        formatter: function (value: string) {
                            if (value.indexOf('（') != -1) {
                                return value.split('（').join('\n'+'（')
                            } else {
                                let res = "";
                                for (let i = 0;i<value.length;i += 4) {
                                    res += value.substring(i,i+4)+'\n'
                                } 
                                return res
                            }
                        }
                    },
                }
            ],
            yAxis: [
                {
                    type: 'value',
                    name: '挂科人数',
                    minInterval: 1,
                    axisLabel: {
                        formatter: '{value} 人'
                    },
                    nameTextStyle: {
                        fontSize: '16'
                    }
                },
                {
                    type: 'value',
                    name: '不及格比例',
                    axisLabel: {
                        formatter: '{value} %'
                    },
                    nameTextStyle: {
                        fontSize: '16'
                    }
                }
            ],
            series: [
                {
                    name: '挂科人数',
                    type: 'bar',
                    smooth: false,
                    barWidth: 30,
                    tooltip: {
                        valueFormatter: function (value: string) {
                            return value + ' 人';
                        }
                    },
                    data: failedNum,
                    itemStyle: {
                        normal: {
                            label: {
                                show: true,
                                position: 'insideBottom',
                                textStyle: {
                                    color: 'black',
                                    fontSize: 12,
                                },
                                formatter: function(realData:any) {
                                    return realData.value+'人'
                                }
                            }
                        }
                    }
                },
                {
                    name: '不及格比例',
                    type: 'line',
                    smooth: false,
                    yAxisIndex: 1,
                    tooltip: {
                        valueFormatter: function (value: string) {
                            return value + ' %';
                        }
                    },
                    data: failedRate,
                    itemStyle: {
                        normal: {
                            label: {
                                show: true,
                                position: 'top',
                                textStyle: {
                                    color: 'black',
                                    fontSize: 12,
                                },
                                formatter: function(realData:any) {
                                    return realData.value+'%'
                                }
                            }
                        }
                    }
                }
            ]
        };
        // 绘制图表
        option && myChart.setOption(option);
        window.addEventListener('resize', () => {
            myChart.resize()
        })
    })
})
</script>
<style scoped>
.chart {
    width: 100%;
    height: 500px;
}
</style>