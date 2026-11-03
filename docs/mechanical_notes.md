# M0 mechanical fit review — T30-FATHE

Mechanical Lead: **Ahmad Nasser**, role confirmed by Ahmad on 4 November
2026. This checklist was prepared with Codex documentation assistance.
Ahmad reported reviewing the proposed patch with ChatGPT; final approval
of the revised version and any physical measurements remain outstanding. It does not certify
physical fit, constitute CAD, or claim Ahmad performed measurements.

## Available evidence and limits

- Existing parts draft proposes two N20 encoder motors, 32–34 mm wheels
  with a 3 mm D-bore, five ToF modules and a 2S 300–500 mAh battery.
  These are planning descriptions, not verified dimensions or selected SKUs.
- **Wheel-bore/N20-shaft compatibility is NOT VERIFIED.** A nominal 3 mm
  D-bore description does not establish the selected motor's shaft diameter,
  flat geometry, engagement length or hub retention. Exact part specifications
  and fit evidence are required before approving the pairing.
- Existing draft mentions a roughly 100 x 110 mm footprint and 3–5 mm
  ground clearance. Neither is an adopted dimension or an official limit.
  The footprint is a draft concept from `docs/M0_previous_teams_review.md`;
  the clearance is a planning value from `docs/parts_list.md`.
- No CAD, component dimension drawings, measured hardware photos, official
  brief or milestone PDFs were available in the inspected workspace.
- Physical compatibility is **NOT VERIFIED**. Do not release a chassis or
  order dimension-sensitive parts based on generic N20/ESP32 labels.

## Measurements and evidence to collect

Record each value in mm with source/SKU/date and measurement uncertainty.
Photos need a ruler/caliper in the same plane; provide orthogonal top/side
views. A dimensioned manufacturer drawing is preferable to scaled photos.

| Item | Exact missing dimensions / checks | Evidence / result |
| --- | --- | --- |
| Official maze constraints | Clear corridor width, cell/wall dimensions, maximum robot envelope/height/mass if specified | [Brief page and values required] |
| Both motor assemblies | Gearbox cross-section; full motor+encoder+connector length; shaft diameter/profile/protrusion; bracket holes and fixing method; left/right orientation | [Exact SKU drawing or measured top/side views required] |
| Wheels and hubs | Actual outer diameter/width; D-bore diameter/flat; hub depth/offset; retention; shaft engagement; tire clearance and runout | [Drawing and shaft/hub fit evidence required] |
| Chassis and supports | Outer footprint including wheels/brackets; thickness; axle position; skid/caster dimensions; lowest underside point; fastener protrusion | [Dimensioned sketch/CAD required] |
| Battery | Pack length/width/thickness including leads and connector; mass; mounting/retention; removal and charging access | [Selected pack drawing/photos required] |
| ESP32/driver/regulators/prototype PCB | Full board dimensions and installed height; holes/standoffs; USB/terminal/header/cable access; enclosure clearance | [Selected board drawings required] |
| Five ToF modules | Board dimensions/holes; optical center; front/side/diagonal sight lines; wall/tire/chassis occlusion; connector access | [Layout and exact breakout drawing required] |
| Harness/switch/buttons | Connector mating space, wire paths/bend space, battery strain relief, operator access | [Top/side layout/photos required] |
| Mass and balance | Actual component masses; battery location; total installed mass; support polygon and center-of-mass estimate | [Measured or sourced mass ledger required] |

## Fit checks before approving the design

- [ ] Confirm official constraints and exact component SKUs; distinguish bought parts from candidate listings.
- [ ] Confirm wheel bore/shaft engagement and secure mounting without loading encoder connectors.
- [ ] Place complete motor/encoder bodies, boards, battery and connectors in a dimensioned layout; verify no interference.
- [ ] Check footprint including wheels and fasteners in straight corridors and throughout turns; show clearance margin.
- [ ] Verify ground clearance at the lowest screw/skid/wire under load; target remains a team decision.
- [ ] Check sensor view and mounting rigidity, accessible reset/start/USB, battery retention/removal and wire routing.
- [ ] Record dimensions, masses, uncertainties, unresolved issues and student reviewer/date before claiming fit.

For a rectangular envelope centered on a point-turn axle, a conservative
planar rotation envelope is a circle with diameter `sqrt(width^2 + length^2)`.
The draft 100 x 110 mm concept would yield about **148.7 mm**, before any
external protrusions or clearance margin. This is a calculation using draft
numbers, not a measured chassis or proof it fits the course maze. For an
off-center axle, use twice the largest distance from the turn center to an
outer point. Recalculate for the actual full envelope and official corridor.

## Review record to fill personally

- Confirmed parts/SKUs and dimension sources: [required]
- Official constraints and proposed clearances: [required]
- Actual layout/CAD/measurement evidence: [required]
- Fit problems and changes made by Ahmad: [actual work only]
- Accepted unresolved risks / next checks: [required]
- Ahmad's corrections and approval/date: [required]

No CAD, fit measurements, purchases, prior-team observations or physical
validation have been fabricated. Electrical approval (including motor
voltage/current and power regulation) requires the Electronics/Motion Leads'
selected component data; this document does not approve those choices.
