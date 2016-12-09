#include "iscore_addon_presetstate.hpp"
#include <PresetState/Inspector/WidgetFactory.hpp>
#include <PresetState/Commands/PresetStateCommandFactoryKey.hpp>
#include <PresetState/Factory.hpp>
#include <PresetState/Executor/StateComponent.hpp>

#include <Inspector/InspectorWidgetFactoryInterface.hpp>
#include <Process/ProcessFactory.hpp>
#include <iscore/plugins/customfactory/StringFactoryKey.hpp>
#include <iscore/plugins/customfactory/FactoryFamily.hpp>
#include <iscore/plugins/customfactory/FactorySetup.hpp>

#include <unordered_map>
#include <iscore_addon_presetstate_commands_files.hpp>
iscore_addon_presetstate::iscore_addon_presetstate() :
    QObject {}
{
}

iscore_addon_presetstate::~iscore_addon_presetstate()
{

}

std::vector<std::unique_ptr<iscore::InterfaceBase>> iscore_addon_presetstate::factories(
        const iscore::ApplicationContext& ctx,
        const iscore::InterfaceKey& key) const
{
    return instantiate_factories<
            iscore::ApplicationContext,
    TL<
        FW<Process::StateProcessFactory,
             PresetState::Factory>,
        FW<Process::StateProcessInspectorWidgetDelegateFactory,
             PresetState::Inspector::Factory>,
        FW<Engine::Execution::StateProcessComponentFactory,
             PresetState::Executor::StateProcessComponentFactory>
    >>(ctx, key);
}

std::pair<const CommandGroupKey, CommandGeneratorMap> iscore_addon_presetstate::make_commands()
{
    using namespace PresetState;
    std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{
        PresetState::CommandFactoryName(),
                CommandGeneratorMap{}};

    using Types = TypeList<
#include <iscore_addon_presetstate_commands.hpp>
      >;
    for_each_type<Types>(iscore::commands::FactoryInserter{cmds.second});


    return cmds;
}

iscore::Version iscore_addon_presetstate::version() const
{
    return iscore::Version{1};
}

UuidKey<iscore::Plugin> iscore_addon_presetstate::key() const
{
    return_uuid("8da162be-f8fb-4958-a49a-9e9571c5d969");
}
