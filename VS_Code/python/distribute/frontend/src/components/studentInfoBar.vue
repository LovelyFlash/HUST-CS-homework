<template>
    <div ref="studentInfoBarRef" class="chart">
        <!-- <p>{{ fatherDataName }}</p> -->
    </div>
</template>

<script setup lang="ts">
import { onMounted, ref, defineProps } from 'vue';
import * as echarts from 'echarts';
import 'echarts/theme/macarons.js';
import { fetchExcellentBarData } from '../api/index';

const props = defineProps({
    chartData: Object,
});
const studentInfoBarRef = ref<HTMLDivElement>()
onMounted(() => {
    // console.log('props.chartData:',props.chartData);
    let data = props.chartData;
    let totalWeightedScoreTerm = data?.totalWeightedScoreTerm;
    let failedSubjectNumsTerm = data?.failedSubjectNumsTerm;
    
    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(studentInfoBarRef.value as HTMLDivElement, 'macarons');
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
                magicType: { show: true, type: ['bar', 'bar'] },
                restore: { show: true },
                saveAsImage: { show: true }
            }
        },
        grid: {
            top: 100,
        },
        legend: {
            data: ['学年加权分', '学年挂科数量']
        },
        xAxis: [
            {
                type: 'category',
                data: ['第一学年上半学期','第一学年下半学期','第二学年上半学期','第二学年下半学期','第三学年上半学期','第三学年下半学期','第四学年上半学期','第四学年下半学期'],
                axisPointer: {
                    type: 'shadow'
                },
                axisLabel: {
                        show: true,
                        interval: 0
                    }
            }
        ],
        yAxis: [
            {
                type: 'value',
                name: '加权分数',
                axisLabel: {
                    formatter: '{value} 分'
                },
                nameTextStyle: {
                    fontSize: '16'
                }
            },
            {
                type: 'value',
                name: '挂科数量',
                minInterval: 1,
                axisLabel: {
                    formatter: '{value} 门'
                },
                nameTextStyle: {
                    fontSize: '16'
                }
            }
        ],
        series: [
            {
                name: '学年加权分',
                type: 'bar',
                tooltip: {
                    valueFormatter: function (value: string) {
                        return value + ' 分';
                    }
                },
                data: totalWeightedScoreTerm,
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
                                return '加权\n'+realData.value+'分'
                            }
                        }
                    }
                }
            },
            {
                name: '学年挂科数量',
                type: 'bar',
                yAxisIndex: 1,
                tooltip: {
                    valueFormatter: function (value: string) {
                        return value + ' 门';
                    }
                },
                data: failedSubjectNumsTerm,
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
                                return realData.value+'门'
                            }
                        }
                    }
                }
            }
        ]
    };
    // 绘制图表
    myChart.setOption(option);
    window.addEventListener('resize', () => {
        myChart.resize()
    })

})
</script>
<style scoped>
.chart {
    width: 1200px;
    height: 400px;
}
</style>