import FWCore.ParameterSet.Config as cms

process = cms.Process("ana")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

process.GlobalTag.globaltag = 'MC_37Y_V5::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) 
) 

process.source = cms.Source("PoolSource",

                            fileNames = cms.untracked.vstring(
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_1.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_2.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_3.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_4.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_5.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_6.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_7.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_8.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_9.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_10.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_11.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_12.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_13.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_14.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_15.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_16.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_17.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_18.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_19.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_20.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_21.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_22.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_23.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_24.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_25.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_26.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_27.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_28.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_29.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_30.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_31.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_32.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_33.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_34.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_35.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_36.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_37.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_38.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_39.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_40.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_41.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_42.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_43.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_44.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_45.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_46.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_47.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_48.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_49.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_50.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_51.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_52.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_53.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_54.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_55.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_56.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_57.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_58.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_59.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_60.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_61.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_62.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_63.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_64.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_65.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_66.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_67.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_68.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_69.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_70.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_71.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_72.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_73.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_74.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_75.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_76.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_77.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_78.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_79.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_80.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_81.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_82.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_83.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_84.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_85.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_86.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_87.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_88.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_89.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_90.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_91.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_92.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_93.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_94.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_95.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_96.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_97.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_98.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_99.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_100.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_101.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_102.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_103.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_104.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_105.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_106.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_107.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_108.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_109.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_110.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_111.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_112.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_113.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_114.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_115.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_116.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_117.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_118.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_119.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_120.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_121.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_122.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_123.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_124.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_125.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_126.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_127.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_128.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_129.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_130.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_131.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_132.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_133.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_134.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_135.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_136.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_137.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_138.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_139.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_140.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_141.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_142.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_143.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_144.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_145.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_146.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_147.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_148.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_149.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_150.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_151.root',
     'file:/scratch/appelte1/JulyExercise/CorrFlow_JEX_MinBias_ZS-v2/CorrFlowSkim_152.root'

),

    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

)


process.load("CondCore.DBCommon.CondDBCommon_cfi")
process.CondDBCommon.connect = "sqlite_file:/gpfs0/home/tuos/CMSSW_3_7_0/src/UserCode/CmsHi/JulyExercise/data/CentralityTables.db"

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
                                      process.CondDBCommon,
                                      toGet = cms.VPSet(cms.PSet(record = cms.string('HeavyIonRcd'),
                                                                 tag = cms.string('HFhits20_DataJulyExercise_AMPT2760GeV_MC_37Y_V5_ZS_v0')
                                                                 )
                                                        )
                                      )

 

process.ana = cms.EDAnalyzer('DataTrans')
  

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("/scratch/tuos/cmssw370/JEX/merged12.root")
                                   )

process.p = cms.Path(process.ana)

